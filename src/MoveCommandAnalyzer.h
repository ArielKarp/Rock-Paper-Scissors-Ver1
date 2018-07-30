/*
 * MoveCommandAnalyzer.h
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#ifndef MOVECOMMANDANALYZER_H_
#define MOVECOMMANDANALYZER_H_

#include "CommandAnalyzer.h"
#include <math.h>


struct MoveCommand {
	int src_col;
	int src_row;
	int dest_col;
	int dest_row;
	int j_col;
	int j_row;
	char j_rep;
};

class MoveCommandAnalyzer: public CommandAnayzer {
public:
	MoveCommandAnalyzer(int a_colls, int a_rows, std::string a_inputFilePath);
	FileStatus getMoveCommand(MoveCommand& a_moveCommand, const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix, bool a_isFirstPlayer);
	FileStatus parseMove(const std::string& a_move, MoveCommand& a_moveCommand, const std::vector<std::vector<BasicPiece*> >* a_piecesMatrix, bool a_isFirstPlayer);
	bool isValidChar(char a_inputChar) override;
	static bool isValidMove(int a_src_x, int a_src_y, int a_dest_x, int a_dest_y);
	MoveCommandAnalyzer& operator=(const MoveCommandAnalyzer& a_commandAnalyzer) = delete;
	MoveCommandAnalyzer (const MoveCommandAnalyzer& a_commandAnalyzer) = delete;
private:

};

#endif /* MOVECOMMANDANALYZER_H_ */
