#ifndef MOSQUITO_H
#define MOSQUITO_H

#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
#include "Board.h"

using namespace std;
using namespace Hive;

class Mosquito : public Token
{
public:
	Mosquito(PlayerColor color,int id) : Token(color, TypeInsect::Mosquito,id, 1) {}

	TypeInsect getType() const override { return TypeInsect::Mosquito; }

	vector<Coordinate> getPossibleMoves() const override;
	vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const override;
	Mosquito *deepCopy() const override
	{
		return new Mosquito(*this);
	}
};

#endif