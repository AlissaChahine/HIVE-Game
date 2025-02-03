#include "Token.h"
#include "Board.h"
#include "Game.h"
#include "Utils.h"

namespace Hive {

bool Token::canMove() const
{
    Game& gameInstance = Game::getInstance();
    if (gameInstance.getMatch().beePlaced(this->getColor()) == false)
    {
        // il faut placer la Bee avant de deplacer
        return false;
    }
    if (this->isActive() == false)
    {
        //cout << "la piece est inative\n";
        return false;
    }
    else // isActive() == true
    {
        const Coordinate& position = getTokenCoordinate();
        Board& boardInstance = Board::getInstance();
        int height = position.getZ();

        for (const auto& token : boardInstance.getData())
        {
            if (Coordinate(position.getX(), position.getY(), height + 1) == token.first)
            {
                // si la piece est bloquee sous une autre
                //cout << "la piece est bloquee sous une autre\n";
                return false;
            }
        }

        // critère ruche unique
        map<Coordinate, Token*> dataCopy = boardInstance.getData(); //copie de la map
        dataCopy.erase(position);
        if (!boardInstance.beehiveIsCompact(dataCopy))
        {
            //si quand on enleve le token la ruche n'est plus unique
            // alors on ne peut pas bouger la piece
            //cout << "la piece briserait la ruche\n";
            return false;
        }

        if (this->getIsSlider() == true)
        {
            int q = position.getX();
            int r = position.getY();
            bool passage = false;
            vector<Coordinate> adjCoord = position.getAdjacentCoordinates();
            for (const auto& adj : adjCoord)
            {
                if (boardInstance.getData().find(adj) == boardInstance.getData().end())
                {
                    if (canSlide(position, adj))
                    {
                        // si il existe au moins une case adj vide telle que canSlide
                        passage = true;
                    }
                }
            }
            if (!passage)
            {
                //cout << "la piece ne peut pas glisser\n";
                return false;
            }
        }
        else // if (isSlider() == false)
        {
            // condition si il existe des moments où les glisseurs sont bloqués
            // prendre en compte si besoins coccinelle/moustique (jumpers)
        }
    }
    return true;
}

void Token::setCoordinate(int x, int y, int z)
{
    if (coordinate == nullptr) {
        coordinate = new Coordinate(x, y, z);
    }
    else { // change coordinates
        coordinate->setX(x);
        coordinate->setY(y);
        coordinate->setZ(z);
    }
    // // Conversion des coordonn?es logiques en graphiques
    // int graphicalX = x * 4 * SCALE;
    // int graphicalY = y * 6 * SCALE;

    // // D?placer l'hexagone ? sa position graphique
    // setPolygon(polygon().translated(graphicalX  * SCALE, graphicalY  * SCALE));
}

void Token::setCoordinate(int x, int y)
{
    if (coordinate == nullptr) {
        coordinate = new Coordinate(x, y);
    }
    else { // change coordinates
        coordinate->setX(x);
        coordinate->setY(y);
    }
    // Conversion des coordonn?es logiques en graphiques
    //int graphicalX = x * 4 * SCALE;
    //int graphicalY = y * 6 * SCALE;
    // D?placer l'hexagone ? sa position graphique
    //setPolygon(polygon().translated(graphicalX  * SCALE, graphicalY  * SCALE));
    // c'est ca qui faisait bug l'affichage

}

bool Token::canSlide(const Coordinate& coord, const Coordinate& dest)const
{
    Board& board = Board::getInstance();
    int q = coord.getX();
    int r = coord.getY();

    Coordinate tab[] =
        {
            {q + 1, r - 1}, {q + 1, r}, {q, r + 1},
            {q - 1, r + 1}, {q - 1, r}, {q, r - 1}
        };

    for (int i = 0; i < 6; ++i) {
        if (tab[i] == dest) {
            //donne les deux cases qui entourent le passage
            Coordinate leftNeighbor = tab[(i + 5) % 6]; //voisin gauche dans le tableau
            Coordinate rightNeighbor = tab[(i + 1) % 6]; //voisin droit dans le tableau

            //vérifie si les voisins du passage sont occupés
            bool leftOccupied = board.getData().find(leftNeighbor) != board.getData().end();
            bool rightOccupied = board.getData().find(rightNeighbor) != board.getData().end();

            //si les deux voisins sont occupés, le passage est bloqué
            if (leftOccupied && rightOccupied) { return false; }
        }
    }
    return true;
}

bool Token::canSlideWithData(const Coordinate& coord, const Coordinate& dest, map<Coordinate, Token*>& board)const
{
    if (coordinate->getZ() == 1)return true; // si la piece est en hauteur 1, elle peut glisser pour redescendre
    int q = coord.getX();
    int r = coord.getY();

    Coordinate tab[] =
        {
            {q + 1, r - 1}, {q + 1, r}, {q, r + 1},
            {q - 1, r + 1}, {q - 1, r}, {q, r - 1}
        };

    for (int i = 0; i < 6; ++i) {
        if (tab[i] == dest) {
            //donne les deux cases qui entourent le passage
            Coordinate leftNeighbor = tab[(i + 5) % 6]; //voisin gauche dans le tableau
            Coordinate rightNeighbor = tab[(i + 1) % 6]; //voisin droit dans le tableau

            //vrifie si les voisins du passage sont occups
            bool leftOccupied = board.find(leftNeighbor) != board.end();
            bool rightOccupied = board.find(rightNeighbor) != board.end();

            //si les deux voisins sont occups, le passage est bloqu
            if (leftOccupied && rightOccupied) { return false; }
        }
    }
    return true;
}

vector<Coordinate> Token::getPossiblePlacements() const
{
    map<Coordinate, Token*>& board = Board::getInstance().getData();
    vector<Coordinate> PossiblePlacements;
    if (isActive()) return PossiblePlacements;
    if (board.empty()) {
        // 1er tour du joueur 1
        PossiblePlacements.insert(PossiblePlacements.end(), Coordinate(0,0));
        return PossiblePlacements;
    }
    if (board.size()==1) {
        // 1er tour du joueur 2
        Coordinate center = Coordinate(0, 0);
        vector<Coordinate> adjCenter = center.getAdjacentCoordinates();
        for (const auto& a : adjCenter)
        {
            PossiblePlacements.insert(PossiblePlacements.end(), a);
        }
        return PossiblePlacements;
    }

    // A partir de 2 pieces deja posees sur le plateau
    vector<Coordinate> colorOnBoard;
    vector<Coordinate> oppositeOnBoard;
    PlayerColor color = getColor();
    for (const auto& t : board)
    {
        //on parcourt tout
        auto tokenOnTop = board.find(Coordinate(t.first.getX(), t.first.getY(), t.first.getZ()+1));
        if (tokenOnTop != board.end())
        {
            if (color == tokenOnTop->second->getColor())
            {
                //cout << "+1 piece de meme couleur \n";
                colorOnBoard.insert(colorOnBoard.end(), t.first);
            }
            else {
                oppositeOnBoard.insert(oppositeOnBoard.end(), t.first);
                //cout << "+1 piece de couleur diff \n";
            }
        }
        else if ((t.second->getColor()) == color)
        {
            if (t.first.getZ()==0 &&
                (colorOnBoard.empty() || find(colorOnBoard.begin(), colorOnBoard.end(), t.first) == colorOnBoard.end()))
            {
                //piece de la meme couleur
                //cout << "+1 piece de meme couleur \n";
                colorOnBoard.insert(colorOnBoard.end(), t.first);
            }
        }
        else // if ((t.second->getColor()) != color)
        {
            if (t.first.getZ()==0 &&
                (oppositeOnBoard.empty() || find(oppositeOnBoard.begin(), oppositeOnBoard.end(), t.first) == oppositeOnBoard.end()))
            {
                // piece de couleur oppose
                oppositeOnBoard.insert(oppositeOnBoard.end(), t.first);
                //cout << "+1 piece de couleur diff \n";
            }
        }
    }

    for (const auto& coord : colorOnBoard)
    {
        // pour chaque coord de piece de meme couleur sur le plateau
        vector<Coordinate> adjCoord = coord.getAdjacentCoordinates();
        for (const auto& adj : adjCoord)
        {
            //cout << "Coord : "<< adj.getX() << ", " << adj.getY() << endl;
            //pour les cases adjacentes a la piece du plateau
            if (board.find(adj) == board.end())
            {
                //si la case est vide
                //cout << "+1 case vide adj : "<<adj.getX()<<","<<adj.getY()<<endl;
                bool oppositeAdj = false;
                for (const auto& adjEmpty : adj.getAdjacentCoordinates())
                {
                    //cout << "on parcourt les cases adj : " << adjEmpty.getX() << "," << adjEmpty.getY() << endl;
                    // pour les cases adj a cette case vide
                    if (find(oppositeOnBoard.begin(), oppositeOnBoard.end(), adjEmpty) != oppositeOnBoard.end())
                    {
                        //cout << "+1 case de color oppose :" << adj.getX() << "," << adj.getY() << endl;
                        oppositeAdj = true;
                    }
                }
                if (!oppositeAdj) // si la case vide n'est a cote d'aucune piece de couleur opposee
                {
                    //cout << "+1 case vide a cote d'uniquement meme color : " << adj.getX() << "," << adj.getY() << endl;
                    if (PossiblePlacements.empty() || find(PossiblePlacements.begin(), PossiblePlacements.end(), adj) == PossiblePlacements.end())
                    {
                        //si la case n'a pas encore ete ajoutee aux possibilites
                        PossiblePlacements.insert(PossiblePlacements.end(), adj);
                        //cout << "ajout dans placements : " << adj.getX() << "," << adj.getY() << endl;
                    }
                }
            }
        }
    }
    return PossiblePlacements;
}

}
