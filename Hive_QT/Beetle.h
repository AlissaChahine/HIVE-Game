// test test
#ifndef BEETLE_H
#define BEETLE_H

#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
#include "Board.h"
using namespace std;
using namespace Hive;

class Beetle : public Token
{
public:
	Beetle(PlayerColor color,int id) : Token(color, TypeInsect::Beetle,id, 0) {}

	TypeInsect getType() const override { return TypeInsect::Beetle; }
	~Beetle() = default;
	vector<Coordinate> getPossibleMoves() const override;
	vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const override;
	Beetle *deepCopy() const override
	{
		return new Beetle(*this);
	}
};

#endif
