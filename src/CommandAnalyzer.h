/*
 * CommandAnalyzer.h
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#ifndef COMMANDANALYZER_H_
#define COMMANDANALYZER_H_

#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <map>
#include "Joker.h"

#define MOVE_NUM_OF_ENTRIES 4
#define MAX_NUM_ENTRIES 8
#define MAX_PATH_LEN 256

enum FileStatus { END_OF_FILE, ERROR, OK, NO_FILE };

class CommandAnayzer {
public:
	CommandAnayzer(int a_colls, int a_rows, std::string a_inputFileName);
	virtual ~CommandAnayzer();
	FileStatus getNextLine(std::string& out_str);
	void splitCommand(const std::string& a_command, std::string& sep, std::vector<std::string>& a_outVec);
	bool setCurrentWorkingDirectory();
	virtual bool isValidChar(char a_inputChar);
	bool isOverRidePlayersPiece(bool a_isFirstPlayer, const BasicPiece* a_boardPiece);
	bool isPlayersPiece(bool a_isFirstPlayer, const BasicPiece* a_boardPiece);
	bool isValidPosition(int a_pos, bool a_isCol); // col- true, o.w. row
	bool isInpuFileStreamGood();
	CommandAnayzer& operator=(const CommandAnayzer& a_commandAnalyzer) = delete;
	CommandAnayzer (const CommandAnayzer& a_commandAnalyzer) = delete;
protected:
	int m_colls;
	int m_rows;
	std::string m_inputFileName;
	std::string m_inputFilePath;
	std::string m_currentWorkingDir;
	std::ifstream* m_inputFileStream;
};

#endif /* COMMANDANALYZER_H_ */
