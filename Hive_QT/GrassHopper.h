#ifndef GRASS_H
#define GRASS_H

#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
#include "Board.h"
using namespace std;
using namespace Hive;

class Grasshopper : public Token
{
public:

	Grasshopper(PlayerColor c, int id) : Token(c, TypeInsect::Grasshopper, id, 0) {};

	~Grasshopper() = default;

	// avoir type en str
	TypeInsect getType() const override { return TypeInsect::Grasshopper; }
	vector<Coordinate> getPossibleMoves() const override;
	vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const override;
	Grasshopper *deepCopy() const override
	{
		return new Grasshopper(*this);
	}
};

#endif
