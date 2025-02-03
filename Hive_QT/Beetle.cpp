// #include "Insects.h"
#include "Utils.h"
#include "Board.h"
#include "Coordinate.h"
#include "Beetle.h"
#include "Match.h"
#include "Token.h"
#include <iostream>
using namespace std;
using namespace Hive;

vector<Coordinate> Beetle::getPossibleMoves() const
{
    return getPossibleMovesByCoordinate(getTokenCoordinate());
}
vector<Coordinate> Beetle::getPossibleMovesByCoordinate(const Coordinate &c) const
{

    /*    map<Coordinate, Token*> board = Board::getInstance().getData();

    vector<Coordinate> moves;
    vector<Coordinate> adjCoordinates = c.getAdjacentCoordinates();
    Board &boardInstance = Board::getInstance();

    for (const auto &coord : adjCoordinates)
    {

        map<Coordinate, Token *> dataCopy = boardInstance.getData(); // copie de la map
        dataCopy.erase(c);                                           // on supprime le token de sa place initiale

        // on rajoute un token temporaire � la bonne place
        dataCopy[coord] = new Beetle(PlayerColor::Black, this->getID());

        // si en plus quand on deplace le token la ruche est toujours unique alors c'est ok
        if (boardInstance.beehiveIsCompact(dataCopy) && canSlide(c, coord))
        {
            // vérifier si la coordonnée existe, dans ce cas mettre la hauteur à 1
            if (boardInstance.getData().find(coord) != boardInstance.getData().end())
            {
                moves.push_back(Coordinate(coord.getX(), coord.getY(), 1));
            }
            else
            {
                moves.push_back(coord);
            }
        }
        dataCopy.erase(coord);
        delete dataCopy[coord];

    }


    return moves;*/

    map<Coordinate, Token*> board = Board::getInstance().getData();

    vector<Coordinate> coordinatesB;
    vector<Coordinate> coordinatesBEmpty;
    // case adjacentes non vides et vides
    const Coordinate& coordBeetle = c;

    vector<Coordinate> adjTab = coordBeetle.getAdjacentCoordinates();


    for (const auto& coord : adjTab) {
        if (board.find(coord) != board.end()) {
            coordinatesB.push_back(coord); // coordonnées adjacentes occupées
        }
        else {
            coordinatesBEmpty.push_back(coord); // coordonnées adjacentes vides
        }
    }

    vector<Coordinate> possibleMoves;

    // Ajouter les cases directement adjacentes occupées (le Beetle peut "monter" dessus)
    for (const auto& coord : adjTab) {
        if (board.find(coord) != board.end()) { // Si la case est occupée
            //et si il n'y a pas deja un token a la coordonnee 1
            if (board.find(Coordinate(coord.getX(), coord.getY(), 1)) == board.end())
            {
                possibleMoves.push_back(Coordinate(coord.getX(), coord.getY(), 1));
            }
        }//ajouter les cases adj libres si beetle sur un autre token, il peut forcément redescendre
        else if(c.getZ()==1)possibleMoves.push_back(coord);
    }

    for (const auto& b : coordinatesB)
    {
        vector<Coordinate> tabB = b.getAdjacentCoordinates();

        for (const auto& c : tabB) //pièces adj à B : c
        {
            if (board.find(c) == board.end()) //si la case est vide, n'est pas dans le plateau
            {
                // doit etre adj a A/Spider
                for (const auto& be : coordinatesBEmpty) //pour chaque pièce adj à A/Spider et vide
                {
                    if (be == c) // c dest visee
                    {
                        if (canSlide(coordBeetle, c) == true) //
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
