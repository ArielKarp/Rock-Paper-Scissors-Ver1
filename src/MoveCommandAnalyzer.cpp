/*
 * MoveCommandAnalyzer.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#include "MoveCommandAnalyzer.h"

MoveCommandAnalyzer::MoveCommandAnalyzer(int a_colls, int a_rows,
		std::string a_inputFilePath) :
		CommandAnayzer(a_colls, a_rows, a_inputFilePath) {
}

FileStatus MoveCommandAnalyzer::getMoveCommand(MoveCommand& a_moveCommand,
		const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix,
		bool a_isFirstPlayer) {
	// if ifstream is NULL, i.e. first move request
	int l_player = (a_isFirstPlayer == true) ? 1 : 2;
	if (!m_inputFileStream) {
		if (!setCurrentWorkingDirectory()) {
			return ERROR;
		}
		m_inputFileStream = new std::ifstream(m_inputFilePath.c_str());
		if (!m_inputFileStream || !m_inputFileStream->good()) {
			std::cout << "Problem with opening move file for player "
					<< l_player << std::endl;
			return NO_FILE;
		}
	}
	std::string l_nextMove;
	FileStatus file_status = getNextLine(l_nextMove);
	if (file_status != OK) {
		return file_status;
	}
	FileStatus parsing_result = parseMove(l_nextMove, a_moveCommand,
			a_piecesMatrix, a_isFirstPlayer);
	return parsing_result;
}

FileStatus MoveCommandAnalyzer::parseMove(const std::string& a_move,
		MoveCommand& a_moveCommand,
		const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix,
		bool a_isFirstPlayer) {
	std::string sep(" ");
	std::vector<std::string> l_moveSplited;
	splitCommand(a_move, sep, l_moveSplited);
	int l_player = (a_isFirstPlayer == true) ? 1 : 2;
	// command is of the following format <from_x> <from_y> <to_x> <to_y> [J: <j_col> <j_row> <new_rep>]
	// check len of returned split
	if (l_moveSplited.size() != 8 && l_moveSplited.size() != 4) {
		std::cout
				<< "Has too many args! the input should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP>, bad move file for player "
				<< l_player << std::endl;
		return ERROR; // failed, too many elements
	}

	for (int i = 0; i < MOVE_NUM_OF_ENTRIES; i++) {
		std::string l_temp_string = l_moveSplited[i];
		if (!std::all_of(l_temp_string.begin(), l_temp_string.end(),
				::isdigit)) { // all chars are digits
			std::cout
					<< "Not all chars are digits! the input should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP> where X Y are digits, bad move file for player "
					<< l_player << std::endl;
			return ERROR;
		}
	}

	// check that location is legal
	int src_col = std::stoi(l_moveSplited[0]);
	int src_row = std::stoi(l_moveSplited[1]);
	int dest_col = std::stoi(l_moveSplited[2]);
	int dest_row = std::stoi(l_moveSplited[3]);

	if (!isValidPosition(src_col, true)) {
		std::cout
				<< "Piece char is not valid! the src col should be between 1 to N! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}
	if (!isValidPosition(src_row, false)) {
		std::cout
				<< "Piece char is not valid! src row should be between 1 to M! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}
	if (!isValidPosition(dest_col, true)) {
		std::cout
				<< "Piece char is not valid! dest col should be between 1 to N! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}
	if (!isValidPosition(dest_row, false)) {
		std::cout
				<< "Piece char is not valid! dest row should be between 1 to M! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}

	if (!isValidMove(src_col, src_row, dest_col, dest_row)) { //not a valid move
		std::cout
				<< "you can move only one to every destination! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}

	// check that the piece can be moved
	if (!(*a_piecesMatrix)[src_row - 1][src_col - 1]->canMove()) {
		std::cout
				<< "The piece you tried to move cannot move!! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}

	// check that moved piece is players piece
	if (!isPlayersPiece(a_isFirstPlayer,
			(*a_piecesMatrix)[src_row - 1][src_col - 1])) {
		std::cout
				<< "The piece you tried to move isn't yours!! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}

	// check that position to move is not occupied by players piece
	if (isOverRidePlayersPiece(a_isFirstPlayer,
			(*a_piecesMatrix)[dest_row - 1][dest_col - 1])) {
		std::cout
				<< "The piece you tried to move, overrides your own!! bad move file for player "
				<< l_player << std::endl;
		return ERROR;
	}

	// set first 4 data entries
	a_moveCommand.src_col = src_col;
	a_moveCommand.src_row = src_row;
	a_moveCommand.dest_col = dest_col;
	a_moveCommand.dest_row = dest_row;

	if (l_moveSplited.size() != 8) {
		// set rest of the data entries
		a_moveCommand.j_col = -1;
		a_moveCommand.j_row = -1;
		a_moveCommand.j_rep = '_';
	} else { // size of move is 8, i.e. we have j position and rep
		// check for J:
		int l_j_location = 4;
		std::string j_string = l_moveSplited[l_j_location];
		if (j_string.size() < 2 || j_string[0] != 'J' || j_string[1] != ':') {
			std::cout
					<< "Wrong input the input should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP>], bad move file for player "
					<< l_player << std::endl;
			return ERROR;
		}

		// check first two elements indicate location
		int l_starting_pos = 5;
		int l_end_pos = 7;
		for (int i = l_starting_pos; i < l_end_pos; i++) {
			std::string l_temp_string = l_moveSplited[i];
			if (!std::all_of(l_temp_string.begin(), l_temp_string.end(),
					::isdigit)) { // all chars are digits
				std::cout
						<< "Has too many args! the output should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP>, bad move file for player "
						<< l_player << std::endl;
				return ERROR;
			}
		}
		// passed check
		int j_col = std::stoi(l_moveSplited[5]);
		int j_row = std::stoi(l_moveSplited[6]);

		// distinct between cases, current moved piece is Joker
		if (a_moveCommand.dest_row == j_row
				&& a_moveCommand.dest_col == j_col) {
			if ((*a_piecesMatrix)[src_row - 1][src_col - 1]->getType()
					!= PieceChar::JOKER) {
				// moved piece is not joker
				std::cout
						<< "Trying to change the rep of something that is not a joker, bad move file for player "
						<< l_player << std::endl;
				return ERROR;
			}

		} else {
			if ((*a_piecesMatrix)[j_row - 1][j_col - 1]->getType()
					!= PieceChar::JOKER) {
				std::cout
						<< "Trying to change the rep of something that is not a joker, bad move file for player "
						<< l_player << std::endl;
				return ERROR; // could not dynamic cast, therefore piece is not joker
			}
		}

		a_moveCommand.j_col = j_col;
		a_moveCommand.j_row = j_row;

		// check that's a valid char
		char new_rep = l_moveSplited[MAX_NUM_ENTRIES - 1][0];
		if (!isValidChar(new_rep)) {
			std::cout
					<< "New rep is not a valid char! bad move file for player!"
					<< l_player << std::endl;
			return ERROR;
		}
		a_moveCommand.j_rep = new_rep;

	}
	return OK;
}

bool MoveCommandAnalyzer::isValidChar(char a_inputChar) {
	// check if inputChar is one the allowed PieceChars
	bool is_valid_char = false;
	switch (a_inputChar) {
	case PieceChar::BOMB:
		is_valid_char = true;
		break;
	case PieceChar::PAPER:
		is_valid_char = true;
		break;
	case PieceChar::ROCK:
		is_valid_char = true;
		break;
	case PieceChar::SCISSORS:
		is_valid_char = true;
		break;
	}
	return is_valid_char;
}

bool MoveCommandAnalyzer::isValidMove(int a_src_col, int a_src_row,
		int a_dest_col, int a_dest_row) {
	if (abs(a_dest_col - a_src_col) == 1 && a_src_row == a_dest_row) {
		return true;
	}
	if (a_src_col == a_dest_col && abs(a_dest_row - a_src_row) == 1) {
		return true;
	}
	return false;
}

