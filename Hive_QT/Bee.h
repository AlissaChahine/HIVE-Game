#ifndef BEE_H
#define BEE_H

#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
#include "Board.h"
using namespace std;
using namespace Hive;

class Bee : public Token
{
public:
    Bee(PlayerColor color,int id) : Token(color, TypeInsect::Bee,id, 1) {}

    TypeInsect getType() const override { return TypeInsect::Bee; }

    vector<Coordinate> getPossibleMoves() const override;
    vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const override;
    Bee *deepCopy() const override
    {
        return new Bee(*this);
    }
};

#endif
