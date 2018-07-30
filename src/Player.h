/*
 * Player.h
 *
 *  Created on: Mar 29, 2018
 *      Author: ariel
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "MoveCommandAnalyzer.h"
#include "PositionCommandAnalyzer.h"

enum PosStatus {POS_ERROR, GOOD, FILE_OPEN_ERROR };


struct BattleRep {
	BasicPiece* pieceToPosition;
	int dest_row;
	int dest_col;
};

class Player {
public:
	Player(int a_playerID, std::string a_positionFileName, std::string a_movesFileName, std::vector<BasicPiece*> a_piecesVector, int a_colls, int a_rows, bool a_isFirst);
	~Player();

	int getPlayerID() const;

	int getLineNum() const;

	void setLineNum(int a_num);

	void updatePointsCount();

	PosStatus initPlayer(std::vector<std::vector<BasicPiece*> >* a_piecesMatrix, const std::vector<std::pair<char, int> >& a_piecesLimit, std::vector<BattleRep>& a_battleToPerform);

	void placePiece(const PositionCommand& a_posCommand, std::vector<std::vector<BasicPiece*> >* a_piecesMatrix, std::vector<BattleRep>& a_battleToPerform);

	FileStatus doNextMove(std::vector<std::vector<BasicPiece*> >* a_piecesMatrix, MoveCommand &a_outCommand);

	void reducePiecesCount(const BasicPiece* a_piece);

	void increasePiecesCount(const BasicPiece* a_piece);

	friend bool operator==(const Player& a_lhs, const Player& a_rhs);

	int findVecPieceIndex(const BasicPiece* a_piece);

	BasicPiece* getPointerToPiece(const char& a_lookup, const char &a_rep);

	int getCountOfPiece(const char& a_lookup);

	int getCountOfJokerType(const char& a_lookup);

	bool havePiecestoMove();

	int getLimitByPiece(const std::vector<std::pair<char, int> >& a_piecesLimit, const char& a_lookup);

	bool isPositionOnBoardByLimit(const std::vector<std::pair<char, int> >& a_piecesLimit);

	void printPiecesCount();

	bool getEOF() const;

	void setEOF(bool a_eof);

	MoveCommandAnalyzer* getMoveAnalyzer();
	PositionCommandAnalyzer* getPositionAnalyzer();


	Player& operator=(const Player& a_player) = delete; // disable operator=
	Player(const Player& a_player) = delete; // disable copy c'tor

private:
	int m_playerID;
	int m_pointsCount;
	int m_lineFailed;
	bool m_isFirst;
	bool m_eof;
	MoveCommandAnalyzer* m_moveAnalyzer;
	PositionCommandAnalyzer* m_posAnalyzer;
	std::vector<std::pair<BasicPiece*, int> > m_piecesCount;
};

#endif /* PLAYER_H_ */
