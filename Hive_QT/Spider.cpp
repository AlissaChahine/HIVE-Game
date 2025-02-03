#pragma once

#include "Spider.h"
#include "Board.h"
#include "Utils.h"

namespace Hive {
// Board : map<Coordinate, Token> data;

vector<Coordinate> Spider::getPossibleNextSlides(const Coordinate& token, map<Coordinate, Token*>& board) const
{
    vector<Coordinate> coordinatesB;
    vector<Coordinate> coordinatesBEmpty;
    // case non vide adj qui existe b, parmis des cases non vides adj à A/spider : B
    // case avec piece spider A
    const Coordinate& coordSpider = token;

    vector<Coordinate> adjTab = coordSpider.getAdjacentCoordinates();

    for (const auto& coord : adjTab)
    {
        if (board.find(coord) != board.end())
        {
            coordinatesB.insert(coordinatesB.end(), coord); //coord adj à A (Spider) non vides
        }
        else // if (board.find(coord) == board.end()), pas dans le plateau
        {
            coordinatesBEmpty.insert(coordinatesBEmpty.end(), coord); //coord adj à A (Spider) et vides
        }
    }

    // peut se déplacer UNIQUEMENT aux espaces vide qui sont adj à A ET B (A et n'importe quelle b)
    // on arrive sur une case vide cMove1 parmis un choix de cases possibles C : firstPossibleMoves
    vector<Coordinate> possibleCoordinatesNextSlide;
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
                        if (canSlideWithData(coordSpider, c, board) == true) //
                        {
                            possibleCoordinatesNextSlide.insert(possibleCoordinatesNextSlide.end(), c);
                        }
                    }
                }
            }
        }
    }
    return possibleCoordinatesNextSlide;
}

vector<Coordinate> Spider::getPossibleMovesByCoordinate(const Coordinate& c) const
{
    map<Coordinate, Token*> board = Board::getInstance().getData();
    vector<Coordinate> possibleMoves;
    const Coordinate& coordSpider = c;
    auto it = board.find(coordSpider);
    if (it == board.end())
    {
        cout << "Spider moves error : aucun token a cette coordonee;";
        return possibleMoves;
    }
    // !!!! si on laisse ca boucle a cause de canmove qui appelle getpossibleMoves
    // deja test dans canmove/game
    /*  else if (it->second->canMove() == false)
        {
            cout << "Spider moves error : ce token ne peut pas move;";
            return possibleMoves;
        }*/
    // auto& saveIt = *it;
    board.erase(it); // la position de base sera vide apres deplacement
    vector<Coordinate> possibleFirstSlides;
    possibleFirstSlides = getPossibleNextSlides(coordSpider, board);

    // Pour chaque 1er deplacement possible
    for (const auto& firstSlide : possibleFirstSlides)
    {
        //cout << "1er Slide : " << "(" << firstSlide.getX() << ", " << firstSlide.getY() << ")" << endl;
        vector<Coordinate> possible2ndSlides;
        // board.erase(firstSlide);
        possible2ndSlides = this->getPossibleNextSlides(firstSlide, board);
        auto it = find(possible2ndSlides.begin(), possible2ndSlides.end(), coordSpider);
        if (it != possible2ndSlides.end()) possible2ndSlides.erase(it);
        // on supprime des 2emes deplacements possibles la case avant precedente (point 0)

        // Pour chaque 2eme deplacement possible
        for (const auto& secondSlide : possible2ndSlides)
        {
            //cout << "2eme Slide : " << "(" << secondSlide.getX() << ", " << secondSlide.getY() << ")" << endl;
            vector<Coordinate> possible3rdSlides;
            possible3rdSlides = this->getPossibleNextSlides(secondSlide, board);
            auto it = find(possible3rdSlides.begin(), possible3rdSlides.end(), firstSlide);
            possible3rdSlides.erase(it);
            // on supprime des 3emes deplacements possibles la case avant precedente (1er deplacement choisit)

            // Pour chaque 3eme deplacement possible
            for (const auto& thirdSlide : possible3rdSlides)
            {
                //cout << "3eme Slide : " << "(" << thirdSlide.getX() << ", " << thirdSlide.getY() << ")" << endl;
                //cout << "\n";
                // si la case n'est pas deja dans les destinations possibles
                if (find(possibleMoves.begin(), possibleMoves.end(), thirdSlide) == possibleMoves.end())
                {
                    possibleMoves.insert(possibleMoves.end(), thirdSlide);
                }
            }
        }
    }
    //board.insert(saveIt); // on remet l'araignee a sa position initiale
    return possibleMoves;
}


vector<Coordinate> Spider::getPossibleMoves() const
{
    return getPossibleMovesByCoordinate(getTokenCoordinate());
}
}

