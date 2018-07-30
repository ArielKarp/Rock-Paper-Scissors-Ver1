/*
 * Joker.h
 *
 *  Created on: Mar 29, 2018
 *      Author: gasha
 */

#ifndef JOKER_H_
#define JOKER_H_
#include "BasicPiece.h"

class Joker: public BasicPiece {
public:
	Joker(char a_symbol, bool a_isUpper);
	void setSymbol(const char& a_symbol);
	virtual char getType() const override;
	friend std::ostream& operator<<(std::ostream& os, const Joker& a_joker);

private:
};



#endif /* JOKER_H_ */
