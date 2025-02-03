#include "Ladybug.h"
#include "Board.h"
using namespace std;
using namespace Hive;

vector<Coordinate> Ladybug::getPossibleMoves() const
{
    map<Coordinate, Token*> board = Board::getInstance().getData();
    return getPossibleMovesByCoordinate(getTokenCoordinate());
}

vector<Coordinate> Ladybug::getNextPossibleJump(const Coordinate& c)const
{
    map<Coordinate, Token*> board = Board::getInstance().getData();
    //ici ps besoin de verifier si la ruche est compacte car elle l'est forcément après qu'on monte sur une pièce
    //si(canmove est valide)
    vector<Coordinate> moves;
    vector<Coordinate> adjCoordinates = c.getAdjacentCoordinates();
    Board& boardInstance = Board::getInstance();

    for (const auto& coord : adjCoordinates)
    {
        if (board.find(coord) != board.end()) //si different de nullptr donc si la case est pleine
        {
            moves.push_back(coord);//on ajoute dans les moves possible
        }
    }
    return moves;
}

vector<Coordinate> Ladybug::getNextPossibleSlide(const Coordinate& c)const
{
    map<Coordinate, Token*> board = Board::getInstance().getData();
    vector<Coordinate> moves;
    vector<Coordinate> adjCoordinates = c.getAdjacentCoordinates();
    Board& boardInstance = Board::getInstance();

    for (const auto& coord : adjCoordinates)
    //ici pas besoin de verifier si la ruche est compacte car elle l'est forcément après qu'on descends d'une pièce
    //si(canmove est valide)
    {
        if (board.find(coord) == board.end()) //si egal a nullptr donc si la case et vide
        {
            moves.push_back(coord);//on ajoute dans les moves possibles
        }
    }
    return moves;
}

vector<Coordinate> Ladybug::getPossibleMovesByCoordinate(const Coordinate& c) const
{
    map<Coordinate, Token*> board = Board::getInstance().getData();
    vector<Coordinate> allMoves;
    vector<Coordinate> firstMoves = getNextPossibleJump(c);

    for (const auto& move1 : firstMoves)//regarde les sauts possibles parmi ceux la
        {
        vector<Coordinate> secondMoves = getNextPossibleJump(move1);
        
        //on retire la coordonnee d ou on vient des choix possibles
        auto it = find(secondMoves.begin(), secondMoves.end(), c);
        if (it != secondMoves.end()) secondMoves.erase(it);
        
        for (const auto& move2 : secondMoves)//regarde les slides possibles parmi ceux la
        {
            vector<Coordinate> thirdMoves = getNextPossibleSlide(move2);
            //si on ne peux pas faire les trois moves, on abandonne a route
            allMoves.insert(allMoves.end(), thirdMoves.begin(), thirdMoves.end());
            //on ajoute tous les troisiemes moves possibles à allMoves
        }
    }
    return allMoves;
}
