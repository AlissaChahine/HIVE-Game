#ifndef IA_H
#define IA_H
#include "Utils.h"
#include "Player.h"
#include "Token.h"
#include <cstdlib>
#include <ctime>
using namespace std;

namespace Hive {

    class IA : public Player {
    private:
        int difficultyLevel;
    public:
        IA(PlayerColor c, const string& n, int difficulty) : Player(c, n, true), difficultyLevel(difficulty) {}

        //getter pour le niveau de difficulté
        int getDifficultyLevel() const { return difficultyLevel;}

        //setter pour le niveau de difficulté
        void setDifficultyLevel(int level) { difficultyLevel = level;}

        int calculateDistanceFromWhiteBee(const Coordinate& initialToken) const;
        //Coordinate getWhiteBeeCoordinate();
        Coordinate choseMoveOrPlacement(const std::vector<Coordinate>& possibleMovesOrPlacements, Token* chosenToken) const;
        Token* choseTokenFromHand()const;
        Token* choseTokenFromBoard() const;
        Token* IA_whatToMove() const ;
        virtual Coordinate IA_whereToMove(Token* chosenToken) const ;
		virtual bool whiteBeeIsNeighbour(Token* token) const;
    };

}
#endif
