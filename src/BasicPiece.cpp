/*
 * BasicPiece.c
 *
 *  Created on: Mar 29, 2018
 *      Author: gasha
 */


#include "BasicPiece.h"

//constructor
BasicPiece::BasicPiece():
m_symbol(EMPTY), m_isUpper(true){}


BasicPiece::BasicPiece(char a_symbol, bool a_isUpper) :
		m_symbol(a_symbol),m_isUpper(a_isUpper){
}

//simple getters

char BasicPiece::getSymbol() const{
	return m_symbol;
}

char BasicPiece::getUpper() const{
	return m_isUpper;
}

bool BasicPiece::canMove() const{
	// checks whether the symbol on board can move - whether it's RSP
	switch(m_symbol){
		case PieceChar::BOMB:
			return false;
		case PieceChar::EMPTY:
			return false;
		case PieceChar::FLAG:
			return false;
		}
	return true;
}

//operators overloading

bool operator==(const BasicPiece& a_lhs, const BasicPiece& a_rhs){
	// two pieces are equal if there symbol is the same (not case sensitive)
	if (toupper(a_lhs.getSymbol()) == toupper(a_rhs.getSymbol())){
		return true;
	}
	return false;
}

bool operator<(const BasicPiece& a_lhs, const BasicPiece& a_rhs){
	// checks whether the piece is smaller than another. returns true if it looses in the battle.
	if ((toupper(a_lhs.getSymbol())) == (toupper(a_rhs.getSymbol()))){
		return false;
	}
	else if ((toupper(a_lhs.getSymbol()) == EMPTY) || (toupper(a_lhs.getSymbol()) == FLAG)){
		return true;
	}
	else if (toupper(a_lhs.getSymbol()) == BOMB){
		return false;
	}
	else if ((toupper(a_lhs.getSymbol()) == ROCK) && (toupper(a_rhs.getSymbol()) == PAPER)){
		return true;
	}
	else if ((toupper(a_lhs.getSymbol()) == PAPER) && (toupper(a_rhs.getSymbol()) == SCISSORS)){
		return true;
	}
	else if ((toupper(a_lhs.getSymbol()) == SCISSORS) && (toupper(a_rhs.getSymbol()) == ROCK)){
		return true;
	}
	return false;
}


std::ostream& operator<<(std::ostream& os, const BasicPiece& a_piece){
	// prints the symbol - if the symbol is empty - prints a space
	if (a_piece.getSymbol() == EMPTY){
		os << " ";
	}
	else{
		// prints the symbol (case sensitive)
		if (a_piece.getUpper() == true){
			os << a_piece.getType();
		}
		else{
			os << char(tolower(a_piece.getType()));
		}
	}
	return os;
}

char BasicPiece::getType() const {
	return m_symbol;
}


