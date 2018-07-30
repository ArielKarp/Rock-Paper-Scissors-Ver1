/*
 * PositionCommandAnalyzer.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#include "PositionCommandAnalyzer.h"

PositionCommandAnalyzer::PositionCommandAnalyzer(int a_colls, int a_rows,
		std::string a_inputFilePath) :
		CommandAnayzer(a_colls, a_rows, a_inputFilePath) {
}

FileStatus PositionCommandAnalyzer::getPosCommand(PositionCommand& a_posCommand,
		bool a_isFirst,
		const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix) {
	// if ifstream is NULL, i.e. first move request
	int l_player = (a_isFirst == true) ? 1 : 2;
	if (!m_inputFileStream) {
		if (!setCurrentWorkingDirectory()) {
			return ERROR;
		}
		m_inputFileStream = new std::ifstream(m_inputFilePath.c_str());
		if (!m_inputFileStream || !m_inputFileStream->good()) {
			std::cout << "Problem with opening file positioning for player "
					<< l_player << std::endl;
			return NO_FILE;
		}
	}
	std::string l_nextPos;
	//gets next line
	FileStatus file_status = getNextLine(l_nextPos);
	if (file_status != OK) {
		return file_status;
	}
	// returns the struct filled!
	bool parsing_result = parsePosition(l_nextPos, a_posCommand, a_isFirst,
			a_piecesMatrix);
	if (parsing_result == false) {
		return ERROR;
	}
	return OK;
}

bool PositionCommandAnalyzer::isValidChar(char a_inputChar, bool a_isJoker) {
	// checks whether it is a valid char for pos command -
	switch (a_inputChar) {
	case PieceChar::FLAG:
		if (a_isJoker == true) {
			return false;
		} else {
			return true;
		}
	case PieceChar::BOMB:
		return true;
	case PieceChar::PAPER:
		return true;
	case PieceChar::ROCK:
		return true;
	case PieceChar::SCISSORS:
		return true;
	}
	return false;
}

bool PositionCommandAnalyzer::parsePosition(const std::string& a_position,
		PositionCommand& a_posCommand, bool a_isFirst,
		const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix) {
	int l_player = (a_isFirst == true) ? 1 : 2;
	std::string sep(" ");
	std::vector<std::string> l_posSplited;
	// seperates the command according to the separator
	splitCommand(a_position, sep, l_posSplited);

	// command has the following two formats
	// 1. <piece_char> <x_pos> <y_pos>
	// 2. J <x_pos> <y_pos> <piece_char>
	if (l_posSplited.size() != 3 && l_posSplited.size() != 4) {
		std::cout
				<< "Has too many args! the output should be <PIECE CHAR><X><Y> or J<X><Y><PIECE CHAR>, bad position file for player "
				<< l_player << std::endl;
		return false; // failed, too many elements
	}

	bool l_jokerCommand = false;
	if (l_posSplited.size() == 4) { // second type
		if (l_posSplited[0][0] != 'J') {
			std::cout
					<< "wrong format, no J in the begging! the output should be J<X><Y><PIECE CHAR>, bad position file for player "
					<< l_player << std::endl;
			return false;
		}
		a_posCommand.is_j = true;
		l_jokerCommand = true;

	} else {
		a_posCommand.is_j = false;
	}

	//checks whether all char are digits
	int starting_indx = 1;
	for (int i = starting_indx; i < (starting_indx + 2); i++) {
		std::string l_temp_string = l_posSplited[i];
		if (!std::all_of(l_temp_string.begin(), l_temp_string.end(),
				::isdigit)) { // all chars are digits
			std::cout
					<< "Not all chars are digits! the output should be <PIECE CHAR><X><Y> or J<X><Y><PIECE CHAR> where X Y are digits, bad position file for player "
					<< l_player << std::endl;
			return false;
		}
	}

	uint sizeOfSplitted = 3;
	char piece_char =
			l_posSplited.size() == sizeOfSplitted ?
					l_posSplited[0][0] : l_posSplited[sizeOfSplitted][0];

	if (!isalpha(piece_char)) {
		std::cout
				<< "PieceChar is not a char the output should be <PIECE CHAR><X><Y> or J<X><Y><PIECE CHAR>, bad position file for player "
				<< l_player << std::endl;
		return false;  // piece char is not char
	}

	if (!isValidChar(piece_char, l_jokerCommand)) {
		// piece char is not valid
		std::cout
				<< "Piece char is not valid! you placed  a piece that cannot move! bad position file for player "
				<< l_player << std::endl;
		return false;
	}
	// piece char is valid
	a_posCommand.piece_char = piece_char;

	int l_piece_col = std::stoi(l_posSplited[starting_indx]);
	int l_piece_row = std::stoi(l_posSplited[starting_indx + 1]);
	if ((!(isValidPosition(l_piece_row, false)))
			|| (!(isValidPosition(l_piece_col, true)))) {
		// the pos not in the borders of the board
		std::cout
				<< "the position in the borders of the board! 0<X<N+1 0<Y<M+1, bad position file for player "
				<< l_player << std::endl;
		return false;
	}

	if (isOverRidePlayersPiece(a_isFirst,
			(*a_piecesMatrix)[l_piece_row - 1][l_piece_col - 1])) {
		std::cout
				<< "Player overriding it's own piece, bad position file for player "
				<< l_player << std::endl;
		return false;
	}

	a_posCommand.src_col = l_piece_col; //l_piece_row;
	a_posCommand.src_row = l_piece_row;
	return true;
}
