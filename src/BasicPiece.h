/*
 * BasicPiece.h
 *
 *  Created on: Mar 29, 2018
 *      Author: gasha
 */

#ifndef BASICPIECE_H_
#define BASICPIECE_H_
#include <iostream>
#include "Logger.h"
//enum representing all possible pieces on the board, including an empty one
enum PieceChar {
	FLAG = 'F', JOKER = 'J', BOMB = 'B', SCISSORS = 'S', PAPER = 'P', ROCK = 'R', EMPTY = 'E'
};

class BasicPiece {
public:
	//constructor which creates a basic piece using a symbol and a flag if the piece is player 1 or 2
	BasicPiece();
	BasicPiece(char a_symbol, bool a_isUpper=true);
	virtual ~BasicPiece() = default;
	char getSymbol() const; //returns which piece is it
	char getUpper() const; // returns of which player is it (upper/lower)
	bool canMove() const; // only RSP can move]
	virtual char getType() const;
	friend bool operator==(const BasicPiece& a_lhs, const BasicPiece& a_rhs);
	friend bool operator<(const BasicPiece& a_lhs, const BasicPiece& a_rhs);
	friend bool operator>(const BasicPiece& a_lhs, const BasicPiece& a_rhs) { return operator<(a_rhs, a_lhs); };
	friend std::ostream& operator<<(std::ostream& os, const BasicPiece& a_piece);

protected:
	char m_symbol;
	bool m_isUpper;
};



#endif /* BASICPIECE_H_ */
