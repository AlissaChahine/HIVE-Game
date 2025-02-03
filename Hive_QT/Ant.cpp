#include "Ant.h"
#include "Utils.h"
#include "Board.h"
#include "Coordinate.h"
#include "Match.h"
#include "Token.h"
#include <set>
#include <queue>
using namespace std;
using namespace Hive;


vector<Coordinate> Ant::getPossibleMoves() const
{
    return getPossibleMovesByCoordinate(getTokenCoordinate());

}

vector<Coordinate> Ant::getPossibleMovesByCoordinate(const Coordinate& c) const
{

    vector<Coordinate> moves;
    set<Coordinate> visitedCoordinates; // pr ne pas check deux fois la même position
    queue<Coordinate> toVisit;
    toVisit.push(c);
    visitedCoordinates.insert(c);
    // std::vector<Coordinate> adjcoord = c.getAdjacentCoordinates();  // Get adjacent coordinates
    map<Coordinate, Token*> board = Board::getInstance().getData();
    Board& boardInstance = Board::getInstance();
    map<Coordinate, Token*> dataCopy = boardInstance.getData();

    // !!!! si on laisse ca boucle a cause de canmove qui appelle getpossibleMoves
    // deja test dans canmove/game
    //if (canMove()==false) {
    //    cout << "La fourmi ne peut pas être déplacée sans briser la ruche ";
    //    return vector<Coordinate>(); // return vecteur vide
    //}
    // retirer c de board pour boucler dedans

    while (!toVisit.empty()) {
        Coordinate current = toVisit.front();
        toVisit.pop();
        vector<Coordinate> adjCurrent = current.getAdjacentCoordinates();

        for (const Coordinate& voisin : adjCurrent) {
            if (visitedCoordinates.find(voisin) == visitedCoordinates.end()) {
                visitedCoordinates.insert(voisin);
                // check que la pos est vide
                if (board.find(voisin) == board.end()) {
                    // simulation plus canSlide ?
                    Ant* simulatedAnt = new Ant(*this);
                    dataCopy[voisin] = simulatedAnt;
                    dataCopy.erase(c);
                    if (boardInstance.beehiveIsCompact(dataCopy) && canSlide(current, voisin)){
                        moves.push_back(voisin);
                        toVisit.push(voisin);
                    }

                    delete simulatedAnt;
                    dataCopy.erase(voisin); // clean up the simulation

                }
            }

            visitedCoordinates.insert(voisin);
        }
    }


    return moves;
}
