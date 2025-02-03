#ifndef ANT_H
#define ANT_H

#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
#include "Board.h"
using namespace std;
using namespace Hive;

class Ant : public Token
{
public:
    Ant(PlayerColor c,int id) : Token(c, TypeInsect::Ant,id, 1) {}
    ~Ant() = default;

    // avoir type en str
    TypeInsect getType() const override { return TypeInsect::Ant; }
    vector<Coordinate> getPossibleMoves() const override;
    vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const override;
    Ant *deepCopy() const override
    {
        return new Ant(*this);
    }
};

#endif
