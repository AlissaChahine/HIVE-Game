#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
#include "Board.h"
#include "Mosquito.h"
using namespace std;
using namespace Hive;

vector<Coordinate> Mosquito::getPossibleMoves()const
{
    return getPossibleMovesByCoordinate(getTokenCoordinate());
}

vector<Coordinate> Mosquito::getPossibleMovesByCoordinate(const Coordinate& c) const {
    map<Coordinate, Token*> board = Board::getInstance().getData();
    Board& boardInstance = Board::getInstance();
    vector<Coordinate> moves;
    vector<Coordinate> adjCoordinates = boardInstance.getAdjacentTokens(c);
    for (const auto& coord : adjCoordinates) //pour chaque coordonnee des adjacents aux moustique
    {
        //on recupere le token si il existe
        auto it = board.find(coord);
        if (it != board.end() && it->second != nullptr)
        {
            Token* token = it->second;
            //recuperer les moves possibles de ce token
            //on utilise sa propre methode surchargee mais sur les coordonnees du moustique
            vector<Coordinate> movesToken = token->getPossibleMovesByCoordinate(c);

            //si la coordonnee n'est pas deja dans les moves possibles on l'ajoute
            for (const auto& move : movesToken)
            {
                if (find(moves.begin(), moves.end(), move) == moves.end())
                {
                    moves.push_back(move);
                }
            }
        }
    }
    return moves;
}
