/*
 * Game.h
 *
 *  Created on: Mar 29, 2018
 *      Author: gasha
 */

#ifndef GAME_H_
#define GAME_H_
#include "Player.h"
#include <map>
#include <vector>
#include <string>

enum GameStatus {
	PLAYER1_WIN_FLAGS,
	PLAYER2_WIN_FLAGS,
	PLAYER1_WIN_MOVING_PIECES,
	PLAYER2_WIN_MOVING_PIECES,
	TIE,
	TIE_NO_FLAGS,
	PLAYER1_LOSE_BAD_POS,
	PLAYER2_LOSE_BAD_POS,
	TIE_BAD_POS,
	PLAYER1_LOSE_BAD_MOVE,
	PLAYER2_LOSE_BAD_MOVE,
	OPEN_FAIL_FAILED,
	CONTINUE,
	TIE_NO_MOVING
};

class Game {
public:
	Game(int a_N, int a_M, std::vector<std::pair<char, int> >& a_piecesLimit,
			const std::string& a_player1PositionFileName,
			const std::string& a_player1MovesFileName,
			const std::string& a_player2PositionFileName,
			const std::string& a_player2MovesFileName,
			const std::string& a_outPutName);
	~Game();
	Game(const Game& a_game) = delete;
	Game& operator=(const Game& a_game) = delete;

	char getSymbol() const;

	friend std::ostream& operator<<(std::ostream& os, const Game& a_game);

	void playGame();

	void initBoard();

	void doNextMove();

	void checkStatus();

	void updatePiecesMatrix(int a_row, int a_col, BasicPiece* a_piece);

	void switchCurrentPlayer();

	void commenceBattle(const BattleRep& a_inBattle);

	void removePieceFromMatrix(int a_row, int a_col);

	void reducePieceCountOfPlayer(const BasicPiece* a_inPiece);

	void increasePieceCountOfPlayer(const BasicPiece* a_inPiece);

	void performBattles();

	GameStatus checkStatusAfterMove();

	GameStatus getStatus();

	int winnerNumByStatus() const;

	std::string reasonByStatus() const;

	bool createOutputFileStream();

private:
	Player* m_player1;
	Player* m_player2;
	Player* m_current_player;

	std::vector<std::pair<char, int> > m_piecesLimit;

	// Basic pieces pointers
	BasicPiece* m_emptyPiece;

	BasicPiece* m_lowFlagPiece;
	BasicPiece* m_upperFlagPiece;

	BasicPiece* m_lowBombPiece;
	BasicPiece* m_upperBombPiece;

	BasicPiece* m_lowSciPiece;
	BasicPiece* m_upperSciPiece;

	BasicPiece* m_lowPaperPiece;
	BasicPiece* m_upperPaperPiece;

	BasicPiece* m_lowRockPiece;
	BasicPiece* m_upperRockPiece;

	Joker* m_lowJokerBombPiece;
	Joker* m_upperJokerBombPiece;

	Joker* m_lowJokerSciPiece;
	Joker* m_upperJokerSciPiece;

	Joker* m_lowJokerPaperPiece;
	Joker* m_upperJokerPaperPiece;

	Joker* m_lowJokerRockPiece;
	Joker* m_upperJokerRockPiece;

	std::vector<std::vector<BasicPiece*> >* m_piecesMatrix;
	std::vector<BattleRep> m_battleToPerform;

	GameStatus m_status;

	std::ofstream* m_outFileStream;
	std::string m_outFileName;

};

#endif /* GAME_H_ */
