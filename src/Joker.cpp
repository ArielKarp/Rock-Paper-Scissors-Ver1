/*
 * Joker.c
 *
 *  Created on: Mar 29, 2018
 *      Author: gasha
 */

#include "Joker.h"

Joker::Joker(char a_symbol, bool a_isUpper) : BasicPiece(a_symbol, a_isUpper) {
}

//setter to change the symbol
void Joker::setSymbol(const char& a_symbol){
	m_symbol = a_symbol;
}
//prints joker - not the representation!
std::ostream& operator<<(std::ostream& os, const Joker& a_joker){
	if (a_joker.getUpper() == true){
		os << 'J';
	}
	else{
		os << 'j';
	}
	return os;
}

char Joker::getType() const {
	return PieceChar::JOKER;
}
