#include "Grasshopper.h"
#include "Utils.h"
#include "Board.h"
#include "Coordinate.h"
#include "Match.h"
#include "Token.h"
#include <set>
#include <queue>
using namespace std;
using namespace Hive;

vector<Coordinate> Grasshopper::getPossibleMoves() const
{
    return getPossibleMovesByCoordinate(getTokenCoordinate());

}
vector<Coordinate> Grasshopper::getPossibleMovesByCoordinate(const Coordinate& c) const
{

    vector<Coordinate> moves;
    Board& boardInstance = Board::getInstance();
    map<Coordinate, Token*> board = Board::getInstance().getData();
    // définir les directions , quan don choisit une direct on continue tjr dans la même --> moves in a straight line
    vector<Coordinate> directions = {
        {1, -1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}
    };

    for (const auto& dir : directions) {
        Coordinate nextPos = c + dir;
        bool foundPieces = false;

        while (board.find(nextPos) != board.end()) { // on boucle tnat qu'on trouve que des places occupées 
            foundPieces = true; 
            nextPos = nextPos + dir; // thr dans la même direction , operator + ajouté dans classe coordinate
        }
       
        if (foundPieces && board.find(nextPos) == board.end()) {
            // vérif que la regle de la ruche unique est tjr respect 
            map<Coordinate, Token*> dataCopy = board;
            dataCopy.erase(c); 
            Grasshopper* simulatedGrass = new Grasshopper(*this);
            dataCopy[nextPos] = simulatedGrass; 

            if (boardInstance.beehiveIsCompact(dataCopy)) {
                moves.push_back(nextPos); // 
            }
            delete simulatedGrass;
            //dataCopy.erase(nextPos);; 
        }
    }

    return moves;
    
    }