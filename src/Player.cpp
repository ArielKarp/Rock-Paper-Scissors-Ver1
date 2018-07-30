/*
 * Player.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: ariel
 */

#include "Player.h"

Player::Player(int a_playerID, std::string a_positionFileName,
		std::string a_movesFileName, std::vector<BasicPiece*> a_piecesVector,
		int a_colls, int a_rows, bool a_isFirst) :
		m_playerID(a_playerID), m_pointsCount(0), m_isFirst(a_isFirst) {
	// initialize data members to be empty
	m_moveAnalyzer = new MoveCommandAnalyzer(a_colls, a_rows, a_movesFileName);
	m_posAnalyzer = new PositionCommandAnalyzer(a_colls, a_rows,
			a_positionFileName);

	// initialize m_piecesCount
	std::vector<BasicPiece*>::const_iterator it = a_piecesVector.begin();
	for (; it != a_piecesVector.end(); ++it) {
		m_piecesCount.push_back(std::make_pair(*it, int(0)));
	}
	m_lineFailed = -1;
	m_eof = false;
}

Player::~Player() {
	if (m_moveAnalyzer) {
		delete m_moveAnalyzer;
		m_moveAnalyzer = NULL;
	}
	if (m_posAnalyzer) {
		delete m_posAnalyzer;
		m_posAnalyzer = NULL;
	}
}

PosStatus Player::initPlayer(std::vector<std::vector<BasicPiece*> >* a_piecesMatrix,
		const std::vector<std::pair<char, int> >& a_piecesLimit,
		std::vector<BattleRep>& a_battleToPerform) {
	int a_lineCount = 1;
	FileStatus pos_command = OK;
	PositionCommand l_posCommand;
	pos_command = m_posAnalyzer->getPosCommand(l_posCommand , m_isFirst, a_piecesMatrix);
	while (pos_command == OK) {
		a_lineCount+=1;
		placePiece(l_posCommand, a_piecesMatrix, a_battleToPerform);
		pos_command = m_posAnalyzer->getPosCommand(l_posCommand, m_isFirst, a_piecesMatrix);
	}

	if (pos_command == NO_FILE) {
		m_lineFailed = a_lineCount;
		std::cout
				<< "failed to open position file, or state of input stream is bad player number" << getPlayerID()
				<< std::endl;
		return FILE_OPEN_ERROR;
	}
	if (pos_command == ERROR) {
		m_lineFailed = a_lineCount;
		return POS_ERROR;
	}

	if (!isPositionOnBoardByLimit(a_piecesLimit)) {
		m_lineFailed = a_lineCount;
		return POS_ERROR;
	}
	return GOOD;

}

bool Player::isPositionOnBoardByLimit(const std::vector<std::pair<char, int> >& a_piecesLimit) {
	int l_player = (m_isFirst == true) ? 1 : 2;
	std::vector<std::pair<BasicPiece*, int> >::const_iterator it = m_piecesCount.begin();
	for (; it != m_piecesCount.end(); ++it) {
		int l_playersCount = it->second;
		char l_pieceType = it->first->getType();
		int l_gameLimit = getLimitByPiece(a_piecesLimit, l_pieceType);
		if (l_pieceType == PieceChar::FLAG && l_playersCount != l_gameLimit) {  // flag has special case
			std::cout
					<< "Not enough flags, bad position file for player " << l_player
					<< std::endl;
			return false;
		}
		if (l_playersCount > l_gameLimit) {
			// if more that limit were positioned
			std::cout
					<< "Number of player's pieces is more than can be, bad move for player " << l_player
					<< std::endl;
			return false;
		}
	}
	return true;
}

void Player::placePiece(const PositionCommand& a_posCommand, std::vector<std::vector<BasicPiece*> >* a_piecesMatrix, std::vector<BattleRep>& a_battleToPerform) {
	int row = a_posCommand.src_row;
	int col = a_posCommand.src_col;
	BasicPiece* temp_piece;
	if (a_posCommand.is_j){
		temp_piece = getPointerToPiece(PieceChar::JOKER,a_posCommand.piece_char);  // get pointer to piece
	}
	else{
		temp_piece = getPointerToPiece(a_posCommand.piece_char, a_posCommand.piece_char);  // get pointer to piece
	}
	increasePiecesCount(temp_piece);  // increase piece count
	if ( !((*a_piecesMatrix)[row-1][col-1]->getSymbol() == PieceChar::EMPTY)) {
		BattleRep l_battle_to_add;
		l_battle_to_add.dest_col = col-1;
		l_battle_to_add.dest_row = row-1;
		l_battle_to_add.pieceToPosition = temp_piece;
		a_battleToPerform.push_back(l_battle_to_add);
	} else {
		(*a_piecesMatrix)[row-1][col-1] = temp_piece;
	}
}

int Player::getPlayerID() const {
	return m_playerID;
}

int Player::getLineNum() const {
	return m_lineFailed;
}

bool Player::getEOF() const{
	return m_eof;
}

void Player::setLineNum(int a_num) {
	m_lineFailed = a_num;
}

void Player::setEOF(bool a_eof){
	m_eof = a_eof;
}

void Player::updatePointsCount() {
	m_pointsCount++;
}

void Player::increasePiecesCount(const BasicPiece* a_piece) {
	int index = findVecPieceIndex(a_piece);
	m_piecesCount[index].second++;
}

void Player::reducePiecesCount(const BasicPiece* a_piece) {
	int index = findVecPieceIndex(a_piece);
	m_piecesCount[index].second--;
}

int Player::findVecPieceIndex(const BasicPiece* a_piece) {
	std::vector<std::pair<BasicPiece*, int> >::const_iterator it = m_piecesCount.begin();
	int index = 0;
	for (; it != m_piecesCount.end(); ++it) {
		if (it->first == a_piece) {
			return index;
		}
		index++;
	}
	return index;
}

BasicPiece* Player::getPointerToPiece(const char& a_lookup, const char &a_rep) {
	std::vector<std::pair<BasicPiece*, int> >::const_iterator it = m_piecesCount.begin();
	for (; it != m_piecesCount.end(); ++it) {
		if (it->first->getType() == a_lookup) {
			if (it->first->getSymbol() == a_rep){
				return it->first;
			}
		}
	}
	return NULL;  // should never get here
}

int Player::getCountOfJokerType(const char& a_lookup) {
	std::vector<std::pair<BasicPiece*, int> >::const_iterator it = m_piecesCount.begin();
	int l_count = 0;
	for (; it != m_piecesCount.end(); ++it) {
		if (it->first->getType() == PieceChar::JOKER) {
			if (it->first->getSymbol() == a_lookup){
				l_count = it->second;
			}
		}
	}
	return l_count;
}

int Player::getCountOfPiece(const char& a_lookup) {
	std::vector<std::pair<BasicPiece*, int> >::const_iterator it = m_piecesCount.begin();
	int l_count = 0;
	for (; it != m_piecesCount.end(); ++it) {
		if (it->first->getType() == a_lookup) {
			l_count = it->second;
		}
	}
	return l_count;
}

int Player::getLimitByPiece(const std::vector<std::pair<char, int> >& a_piecesLimit, const char& a_lookup) {
	std::vector<std::pair<char, int> >::const_iterator it = a_piecesLimit.begin();
	int l_limit = 0;
	for (; it != a_piecesLimit.end(); ++it) {
		if (it->first == a_lookup) {
			l_limit += it->second;
		}
	}
	return l_limit;
}

FileStatus Player::doNextMove(std::vector<std::vector<BasicPiece*> >* a_piecesMatrix,MoveCommand &a_outCommand) {
	FileStatus rc = m_moveAnalyzer->getMoveCommand(a_outCommand, a_piecesMatrix,
			m_isFirst);
	return rc;
}

void Player::printPiecesCount() {
	std::vector<std::pair<BasicPiece*, int> >::const_iterator it = m_piecesCount.begin();
	for (; it != m_piecesCount.end(); ++it) {
		std::cout << "Piece type: " << it->first->getType() << " Piece char: " << it->first->getSymbol() << " Num: " << it->second << std::endl;
	}
}

bool Player::havePiecestoMove(){
	if ((getCountOfPiece(PieceChar::PAPER)!=0) || ((getCountOfPiece(PieceChar::ROCK)!=0)) || ((getCountOfPiece(PieceChar::SCISSORS)!=0))){
		return true;
	}
	if ((getCountOfJokerType(PieceChar::PAPER)!=0) || ((getCountOfJokerType(PieceChar::ROCK)!=0)) || ((getCountOfJokerType(PieceChar::SCISSORS)!=0))){
		return true;
	}
	return false;
}

MoveCommandAnalyzer* Player::getMoveAnalyzer() {
	return m_moveAnalyzer;
}
PositionCommandAnalyzer* Player::getPositionAnalyzer() {
	return m_posAnalyzer;
}
