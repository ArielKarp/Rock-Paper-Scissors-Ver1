/*
 * CommandAnalyzer.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#include "CommandAnalyzer.h"


CommandAnayzer::CommandAnayzer(int a_colls, int a_rows, std::string a_inputFileName): m_colls(a_colls), m_rows(a_rows), m_inputFileName(a_inputFileName), m_inputFilePath(""), m_currentWorkingDir(""){
	m_inputFileStream = NULL;
}

CommandAnayzer::~CommandAnayzer() {
	if (m_inputFileStream) {
		delete m_inputFileStream;
		m_inputFileStream = NULL;
	}
}

void CommandAnayzer::splitCommand(const std::string& a_command, std::string& sep, std::vector<std::string>& a_outVec) {
	// split the string, C-style
	char* cstr = const_cast<char*>(a_command.c_str());
	char* current;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		a_outVec.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
}

bool CommandAnayzer::setCurrentWorkingDirectory() {
	char temp[MAX_PATH_LEN];
	if (!getcwd(temp, MAX_PATH_LEN)) {
		return false;
	}
	// got cwd, update paths
	m_currentWorkingDir = temp;
	if (m_inputFilePath == "") { // first update of input file path
		m_inputFilePath = m_currentWorkingDir + "/" + m_inputFileName;
	}
	return true;
}


FileStatus CommandAnayzer::getNextLine(std::string& out_str) {
	while (std::getline(*m_inputFileStream, out_str)) {
		// successful read
		// check that line is not empty
		if (out_str.find_first_not_of("\t\n ") != std::string::npos) {
			// line is not empty (contains a char different from \t \n or space
			break;
		}
	}
	// failed to read
	// check inputfilestream
    if((*m_inputFileStream).bad()){
		std::cout
				<< "bad file, unexpected error"
				<< std::endl;
        return ERROR;
    }
    if((*m_inputFileStream).eof()){
    	if (out_str.size() > 0) {
    		return OK; // got to eof after read, but out_str contains data
    	} else {
    		return END_OF_FILE;
    	}
    }
    // otherwise
    return OK;
}

bool CommandAnayzer::isValidChar(char a_inputChar) {
	// check if inputChar is one of the 6 allowed PieceChars
	bool is_valid_char = false;
	switch(a_inputChar){
		case PieceChar::FLAG:
			is_valid_char = true;
			break;
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
		case PieceChar::JOKER:
			is_valid_char = true;
			break;
	}
	return is_valid_char;
}
bool CommandAnayzer::isValidPosition(int a_pos, bool a_isCol) {
	// if a_isCol true, check if a_pos is between [1, M]
	// o.w. a_pos us between [1, N]
	if (a_isCol == true) {
		if (a_pos >= 1 && a_pos <= m_colls) {
			return true;
		} else {
			return false;
		}
	} else {
		if (a_pos >= 1 && a_pos <= m_rows) {
			return true;
		} else {
			return false;
		}
	}
}


bool CommandAnayzer::isOverRidePlayersPiece(bool a_isFirstPlayer, const BasicPiece* a_boardPiece) {
	if (a_boardPiece->getSymbol() == PieceChar::EMPTY) {
		return false;
	}
	if (a_isFirstPlayer) {
		// player is upper case
		if (a_boardPiece->getUpper()) {
			return true;
		} else {
			return false;
		}
	} else {
		// player is lower case
		if (!a_boardPiece->getUpper()) {
			return true;
		} else {
			return false;
		}
	}
}

bool CommandAnayzer::isPlayersPiece(bool a_isFirstPlayer, const BasicPiece* a_boardPiece) {
	if (a_boardPiece->getSymbol() == PieceChar::EMPTY) {
		return false;
	}
	if (a_isFirstPlayer && a_boardPiece->getUpper()) {
		return true;
	}
	if (!a_isFirstPlayer && !a_boardPiece->getUpper()) {
		return true;
	}
	return false;

}

bool CommandAnayzer::isInpuFileStreamGood() {
	if (!m_inputFileStream) { // input file stream is still null
		// create a local file stream
		setCurrentWorkingDirectory();
		std::ifstream l_localFileStream(m_inputFilePath);
		return l_localFileStream.good();
	}

	return m_inputFileStream->good();

}
