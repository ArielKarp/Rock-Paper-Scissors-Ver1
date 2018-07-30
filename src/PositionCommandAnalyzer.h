/*
 * PositionCommandAnalyzer.h
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#ifndef POSITIONCOMMANDANALYZER_H_
#define POSITIONCOMMANDANALYZER_H_

#include "CommandAnalyzer.h"

struct PositionCommand {
	char piece_char;
	int src_col;
	int src_row;
	bool is_j;
};

class PositionCommandAnalyzer: public CommandAnayzer {
public:

	PositionCommandAnalyzer(int a_colls, int a_rows, std::string a_inputFilePath);
	FileStatus getPosCommand(PositionCommand& a_posCommand, bool a_isFirst, const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix);
	bool parsePosition(const std::string& a_position, PositionCommand& a_posCommand, bool a_isFirst, const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix);
	bool isValidChar(char a_inputChar, bool a_isJoker);
	PositionCommandAnalyzer& operator=(const PositionCommandAnalyzer& a_commandAnalyzer) = delete;
	PositionCommandAnalyzer (const PositionCommandAnalyzer& a_commandAnalyzer) = delete;
private:
};

#endif /* POSITIONCOMMANDANALYZER_H_ */
