#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"

namespace Hive {

    class Player {
    private:
        PlayerColor color;
        string name; 
        int score;
        bool isIA;
    public:
        Player(PlayerColor c, const string & n, bool ia=false):color(c),name(n),score(0), isIA(ia) {}
        virtual ~Player() {};
        /*virtual Token* IA_WhatToMove() const;
        virtual Coordinate IA_whereToMove(Token* chosenToken) const;*/
        string getName() const { return name; }
        void setName(string newName) { name = newName; }
        PlayerColor getColor() const { return color; }
        int getScore() const { return score; }
        void setScore(int s) { score += s; }
        void setIA() { isIA = true; }
        bool getIA() const { return isIA; }
    };


    inline std::ostream& operator<<(ostream& f, const Player& p)
    {
        f << p.getName() << " " << p.getColor() << " " << p.getScore() << endl;
        return f;
    }

}

#endif