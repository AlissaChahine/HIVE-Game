#ifndef SPIDER_H
#define SPIDER_H

#include "Token.h"

namespace Hive
{
	class Spider : public Token
	{
	public:
		Spider(PlayerColor c,int id) : Token(c, TypeInsect::Spider,id, 1) {}
		~Spider() {}
		// avoir type en str
		TypeInsect getType() const override { return TypeInsect::Spider; }
		vector<Coordinate> getPossibleMoves() const override;
		vector<Coordinate> getPossibleNextSlides(const Coordinate &token, map<Coordinate, Token*>& board) const;
		vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const override;

		Spider * deepCopy() const override
		{
			return new Spider(*this);
		}
	};

}

#endif
