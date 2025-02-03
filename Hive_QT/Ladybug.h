#ifndef LADYBUG_H
#define LADYBUG_H

#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
#include "Board.h"
using namespace std;
using namespace Hive;

class Ladybug : public Token
{
public:
	Ladybug(PlayerColor color,int id) : Token(color, TypeInsect::Ladybug,id,1) {}

	TypeInsect getType() const override { return TypeInsect::Ladybug; }

	vector<Coordinate> getPossibleMoves() const override;
	vector<Coordinate> getNextPossibleSlide(const Coordinate &c) const;
	vector<Coordinate> getNextPossibleJump(const Coordinate &c) const;
	vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const override;
	Ladybug *deepCopy() const override
	{
		return new Ladybug(*this);
	}
};

#endif