#include "Bee.h"
#include "Board.h"
using namespace std;
using namespace Hive;


//on appelle with coordinate mais avec ses propres coordinate
vector<Coordinate> Bee::getPossibleMoves() const {
    return getPossibleMovesByCoordinate(getTokenCoordinate());
}

vector<Coordinate> Bee::getPossibleMovesByCoordinate(const Coordinate& c) const {
    map<Coordinate, Token*> board = Board::getInstance().getData();

    vector<Coordinate> coordinatesB;
    vector<Coordinate> coordinatesBEmpty;
    // case non vide adj qui existe b, parmis des cases non vides adj  A/spider : B
    // case avec piece bee A
    const Coordinate& coordBee = c;

    vector<Coordinate> adjTab = coordBee.getAdjacentCoordinates();

    for (const auto& coord : adjTab)
    {
        if (board.find(coord) != board.end())
        {
            coordinatesB.insert(coordinatesB.end(), coord); //coord adj  A (Bee) non vides
        }
        else // if (board.find(coord) == board.end()), pas dans le plateau
        {
            coordinatesBEmpty.insert(coordinatesBEmpty.end(), coord); //coord adj  A (Spider) et vides
        }
    }

    // peut se dplacer UNIQUEMENT aux espaces vide qui sont adj  A ET B (A et n'importe quelle b)
    // on arrive sur une case vide cMove1 parmis un choix de cases possibles C : firstPossibleMoves
    vector<Coordinate> possibleMoves;
    for (const auto& b : coordinatesB)
    {
        vector<Coordinate> tabB = b.getAdjacentCoordinates();

        for (const auto& c : tabB) //pices adj  B : c
        {
            if (board.find(c) == board.end()) //si la case est vide, n'est pas dans le plateau
            {
                // doit etre adj a A/Spider
                for (const auto& be : coordinatesBEmpty) //pour chaque pice adj  A/Spider et vide
                {
                    if (be == c) // c dest visee
                    {
                        if (canSlide(coordBee, c) == true) //
                        {
                            possibleMoves.insert(possibleMoves.end(), c);
                        }
                    }
                }
            }
        }
    }
    return possibleMoves;

}

/*
    vector<Coordinate> moves;
    vector<Coordinate> adjCoordinates = c.getAdjacentCoordinates();
    Board& boardInstance = Board::getInstance();

    for (const auto& coord : adjCoordinates)
    {
        if (board.find(coord) == board.end()) //si egal a nullptr donc si la case et vide
        {
            map<Coordinate, Token*> dataCopy = boardInstance.getData();//copie de la map
            dataCopy.erase(c);//on supprime le token de sa place initiale


            //on rajoute un token temporaire  la bonne place
            Token* tempBee = new Bee(PlayerColor::Black, 1);
            dataCopy[coord] = tempBee;

            //si en plus quand on deplace le token la ruche est toujours unique et la piece peut passer alors c'est ok
            if (boardInstance.beehiveIsCompact(dataCopy)&&canSlide(c,coord))
            {
                moves.push_back(coord);//on ajoute dans les moves possibles

            }
            dataCopy.erase(coord);
            delete tempBee;
        }
    }

    return moves;*/
