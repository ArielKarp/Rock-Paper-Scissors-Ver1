/*
 * GameManager.cpp
 *
 *  Created on: Apr 6, 2018
 *      Author: gasha
 */

#include "Game.h"


#define NUM_OF_ROWS 10
#define NUM_OF_COLS 10
#define PLAYER1_BOARD_NAME "player1.rps_board"
#define PLAYER2_BOARD_NAME "player2.rps_board"
#define PLAYER1_MOVES_NAME "player1.rps_moves"
#define PLAYER2_MOVES_NAME "player2.rps_moves"
#define OUTPUT_FILE_NAME   "rps.output"

void fillPiecesCount(std::vector<std::pair<char, int> >& a_piecesLimit) {
	a_piecesLimit.push_back(std::make_pair('R', 2));
	a_piecesLimit.push_back(std::make_pair('P', 5));
	a_piecesLimit.push_back(std::make_pair('S', 1));
	a_piecesLimit.push_back(std::make_pair('B', 2));
	a_piecesLimit.push_back(std::make_pair('J', 2));
	a_piecesLimit.push_back(std::make_pair('F', 1));
}

int main(){

	//std::string l("important value");
	//LOGGER->Log("very important value [%s]!", l.c_str());
	LOGGER->Log("Hello YED, I'm a logger! I'm a very nice guy");
	try {
		std::vector<std::pair<char, int> > l_piecesLimit;
		fillPiecesCount(l_piecesLimit);
		Game l_rsp(NUM_OF_COLS,NUM_OF_ROWS, l_piecesLimit,
				PLAYER1_BOARD_NAME,
				PLAYER1_MOVES_NAME,
				PLAYER2_BOARD_NAME,
				PLAYER2_MOVES_NAME,
				OUTPUT_FILE_NAME);
		l_rsp.playGame();
	} catch (std::bad_alloc&) {
		// If some memory allocation failed
		std::cout << "Failed memory allocation" << std::endl;
	}
}



