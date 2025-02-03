#include "Match.h"
#include <QBrush>
#include <QGraphicsItem>        // Pour QGraphicsItem
#include <QGraphicsTextItem>    // Pour QGraphicsTextItem
#include <QPainter>             // Pour QPainter
#include <QColor>               // Pour QColor
#include <QGraphicsScene>       // Pour QGraphicsScene

void Match::nextTurn()
{
    if (currentplayer == PlayerColor::White)
    {
        currentplayer = PlayerColor::Black;
    }
    else
    {
        currentplayer = PlayerColor::White;
    }
}

Match::Match(std::shared_ptr<Player> white, std::shared_ptr<Player> black, int nb, std::vector<TypeInsect> extension) : playerWhite(white), playerBlack(black), currentplayer(PlayerColor::White), nbPiece(nb)
{
    int i = 0;


    /*whitetokens = new Token *[nbPiece];
    blacktokens = new Token *[nbPiece];*/

    vector<TypeInsect> insects;
    insects.push_back(TypeInsect::Bee);
    insects.push_back(TypeInsect::Spider);
    insects.push_back(TypeInsect::Ant);
    insects.push_back(TypeInsect::Beetle);
    insects.push_back(TypeInsect::Grasshopper);

    for (int k = 0; k < insects.size(); k++)
    {
        switch (insects[k])
        {
        case TypeInsect::Bee:
        {
            i = 1;
            break;
        }
        case TypeInsect::Spider:
        {
            i = 2;
            break;
        }
        case TypeInsect::Ant:
        {
            i = 3;
            break;
        }
        case TypeInsect::Beetle:
        {
            i = 3;
            break;
        }
        case TypeInsect::Grasshopper:
        {
            i = 2;
            break;
        }
        }
        for (int j = 0; j < i; j++)
        {
            /*blacktokens[cmpt] =createToken(PlayerColor::Black, insects[k]);
            whitetokens[cmpt] = createToken(PlayerColor::White, insects[k]);
            cmpt++;*/
            blacktokens.insert(blacktokens.end(),createToken(PlayerColor::Black, insects[k],j+1));
            whitetokens.insert(whitetokens.end(), createToken(PlayerColor::White, insects[k],j+1));
        }
    }
    for (int j = 0; j < extension.size(); j++)
    {
        if (/*cmpt < nbPiece &&*/ extension[j] == TypeInsect::Mosquito)
        {
            /*blacktokens[cmpt] = createToken(PlayerColor::Black, TypeInsect::Mosquito);
            whitetokens[cmpt] = createToken(PlayerColor::White, TypeInsect::Mosquito);*/
            blacktokens.insert(blacktokens.end(), createToken(PlayerColor::Black, TypeInsect::Mosquito,j+1));
            whitetokens.insert(whitetokens.end(), createToken(PlayerColor::White, TypeInsect::Mosquito,j+1));
        }

        if (/*cmpt < nbPiece &&*/ extension[j] == TypeInsect::Ladybug)
        {
            /*whitetokens[cmpt] = createToken(PlayerColor::White, TypeInsect::Ladybug);
            blacktokens[cmpt] = createToken(PlayerColor::Black, TypeInsect::Ladybug);*/

            blacktokens.insert(blacktokens.end(), createToken(PlayerColor::Black, TypeInsect::Ladybug,j+1));
            whitetokens.insert(whitetokens.end(), createToken(PlayerColor::White, TypeInsect::Ladybug,j+1));
        }

        /* cmpt++;*/
    }
}

// void Match::printTokenOnBoard(Token* t)
// {
//     // Créer un pinceau pour la couleur du jeton
//     QBrush brush;

//     if (t->getColor() == PlayerColor::White)
//     {
//         brush.setColor(Qt::white);  // Couleur blanche pour les jetons blancs
//     }
//     else
//     {
//         brush.setColor(Qt::black);  // Couleur noire pour les jetons noirs
//     }

//     brush.setStyle(Qt::SolidPattern);  // Applique un motif solide

//     // Appliquer le pinceau au jeton pour le remplissage
//     t->setBrush(brush);

//     // Définir une bordure jaune pour tous les jetons
//     QPen pen;
//     pen.setColor(Qt::yellow);  // Bordure jaune
//     pen.setWidth(2);  // Largeur de la bordure
//     t->setPen(pen);

//     // Si le jeton a un texte, le rendre jaune
//     t->setTextColor(Qt::yellow);  // Si le jeton contient du texte, ce sera en jaune

//     // Assurez-vous que textItem est bien visible et centré
//     t->updateTextItem();  // Cette méthode va actualiser la position du texte dans l'hexagone

//     // Ajouter le jeton au board
//     addItem(t);
// }

// void Match::displayAllTokens() {
//     // Afficher tous les tokens blancs
//     for (auto token : whitetokens) {
//         printTokenOnBoard(token);
//     }

//     // Afficher tous les tokens noirs
//     for (auto token : blacktokens) {
//         printTokenOnBoard(token);
//     }
// }


Token *Match::createToken(PlayerColor color, TypeInsect type,int j)
{
    switch (type)
    {
    case TypeInsect::Bee:
        return new Bee(color,j);
    case TypeInsect::Spider:
        return new Spider(color,j);
    case TypeInsect::Ant:
        return new Ant(color,j);
    case TypeInsect::Beetle:
        return new Beetle(color,j);
    case TypeInsect::Grasshopper:
        return new Grasshopper(color,j);
    case TypeInsect::Mosquito:
        return new Mosquito(color,j);
    case TypeInsect::Ladybug:
        return new Ladybug(color,j);
    default:
        throw MatchException("Unknown TypeInsect");
    }
}


const Player &Match::getCurrentPlayer() const
{
    if (currentplayer == PlayerColor::White)
        return *playerWhite;
    else
        return *playerBlack;
}

bool Match::isFirstMove() const
{
    if (currentplayer == PlayerColor::White && whiteMoveCount == 0)
        return true;
    if (currentplayer == PlayerColor::Black && blackMoveCount == 0)
        return true;

    return false;
}
bool Match::isFourthMove() const
{
    if (currentplayer == PlayerColor::White && whiteMoveCount == 3)
        return true;
    if (currentplayer == PlayerColor::Black && blackMoveCount == 3)
        return true;

    return false;
}

void Match::incrementCounter()
{
    if (currentplayer == PlayerColor::White)
        whiteMoveCount++;
    else
        blackMoveCount++;
}

bool Match::beeNotPlaced() const
{
    if (currentplayer == PlayerColor::Black && BlackBeePlaced == false)
        return true;
    if (currentplayer == PlayerColor::White && WhiteBeePlaced == false)
        return true;

    return false;
}

bool Match::beePlaced(PlayerColor c) const
{
    if (c == PlayerColor::Black && BlackBeePlaced == false)
        return false;
    if (c == PlayerColor::White && WhiteBeePlaced == false)
        return false;

    return true;
}

void Match::printhand(PlayerColor c) const
{

    for (int i = 0; i < getHand(c).size(); i++)
    {
        cout << (*getHand(c)[i])<<" "<< getHand(c)[i]->getID() << ", ";
    }
    cout << "\n";
}

vector<Token *> Hive::Match::getHand(PlayerColor c) const
{
    vector<Token *> hand;

    if (c == PlayerColor::Black)
    {
        if (isFourthMove() && beeNotPlaced())
        {


            hand.insert(hand.end(), getToken_noplaced(TypeInsect::Bee));

            return hand;

        }
        else
        {
            for (int i = 0; i < nbPiece; i++)
            {
                if (blacktokens[i]->isActive() == false)
                    hand.insert(hand.end(), blacktokens[i]);
            }

        }

    }
    else
    {
        if (isFourthMove() && beeNotPlaced())
        {

            hand.insert(hand.end(), getToken_noplaced(TypeInsect::Bee));
            return hand;


        }
        else
        {
            for (int i = 0; i < nbPiece; i++)
            {
                if (whitetokens[i]->isActive() == false)
                    hand.insert(hand.end(), whitetokens[i]);
            }
        }
    }

    return hand;
}

vector<Token *> Hive::Match::getActiveTokens(PlayerColor c) const
{
    vector<Token *> activeTokens;
    if (isFourthMove() && beeNotPlaced())

    {

        return activeTokens;
    }

    if (c == PlayerColor::Black)
    {


        for (int i = 0; i < nbPiece; i++)
        {
            if (blacktokens[i]->isActive() == true)
                activeTokens.insert(activeTokens.end(), blacktokens[i]);
        }

    }
    else
    {
        for (int i = 0; i < nbPiece; i++)
        {
            if (whitetokens[i]->isActive() == true)
                activeTokens.insert(activeTokens.end(), whitetokens[i]);
        }
    }

    return activeTokens;
}

bool Match::verifyPlacement(Token *token, const Coordinate &coord) const
{

    vector<Coordinate> copie = token->getPossiblePlacements();
    if (find((copie).begin(), (copie).end(), coord) == (copie).end())
        return false;

    return true;
}

bool Match::verifyMoves(Token *token, const Coordinate &coord) const
{
    vector<Coordinate> copie = token->getPossibleMoves();
    if (find((copie).begin(), (copie).end(), coord) == (copie).end())
        return false;
    return true;
}
int Match::placeOnBoard(Token *token, const Hive::Coordinate &coord)
{
    if (token->isActive() == false)

    {

        if (verifyPlacement(token, coord))
        {
            if (isFourthMove() && beeNotPlaced())
            {
                if (token->getInsectType() == TypeInsect::Bee)
                {
                    Board::getInstance().getData().insert(std::pair<Coordinate, Token*>(coord, token));
                    placeBee();
                    incrementCounter();
                    token->setActive();
                    token->setCoordinate(coord.getX(), coord.getY(), coord.getZ());

                    return 1; // 1 ca marche
                }
                else
                    return 0;
            }
            else
            {
                Board::getInstance().getData().insert(std::pair<Coordinate, Token *>(coord, token));
                if (token->getInsectType() == TypeInsect::Bee)
                    placeBee();
                incrementCounter();
                token->setActive();
                token->setCoordinate(coord.getX(), coord.getY(), coord.getZ());
                return 1;
            }
        }
        else
        {

            // throw MatchException("Invalid placement");

            return -1;
        }
    }
    else
    {

        if (verifyMoves(token, coord))

        {

            if (isFourthMove() && beeNotPlaced())
                return 0;
            else
            {

                Board::getInstance().getData().erase(token->getTokenCoordinate());
                Board::getInstance().getData().insert(std::pair<Coordinate, Token *>(coord, token));
                if (token->getInsectType() == TypeInsect::Bee)
                    placeBee();
                incrementCounter();
                token->setCoordinate(coord.getX(), coord.getY(), coord.getZ());
                return 1;
            }
        }
        else
        {

            // throw MatchException("Invalid placement");
            return -1; // ajouter une classe exception c est mieux}
        }
    }
}


void Match::showPlacements(Token *token) const
{
    int n = 1;
    if (token->isActive())
    {
        for (auto i = 0; i < (token->getPossibleMoves()).size(); i++)
            cout << "possibilites de deplacements " << n++ << " : " << (token->getPossibleMoves())[i] << "\n";
    }
    else
    {
        for (auto i = 0; i < (token->getPossiblePlacements()).size(); i++)
            cout << "possibilites de placements " << n++ << " : " << (token->getPossiblePlacements())[i] << "\n";
    }
}


bool Match::checkGameOver()
{

    for (const auto &pair : Board::getInstance().getData())
    {
        if (pair.second->getInsectType() == Hive::TypeInsect::Bee && pair.second->getColor() == Hive::PlayerColor::Black)
        {
            // on teste pour les voisins
            if (Board::getInstance().getData().count(Coordinate(pair.first.getX() + 1, pair.first.getY())) == 1

                && Board::getInstance().getData().count(Coordinate(pair.first.getX(), pair.first.getY() + 1)) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX() - 1, pair.first.getY() + 1)) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX() - 1, pair.first.getY())) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX(), pair.first.getY() - 1)) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX() + 1, pair.first.getY() - 1)) == 1)
            {
                winner = PlayerColor::White;
                return true; // black bee encerclée
            }
        }
        if (pair.second->getInsectType() == Hive::TypeInsect::Bee && pair.second->getColor() == Hive::PlayerColor::White)
        {
            // on teste pour les voisins
            if (Board::getInstance().getData().count(Coordinate(pair.first.getX() + 1, pair.first.getY())) == 1

                && Board::getInstance().getData().count(Coordinate(pair.first.getX(), pair.first.getY() + 1)) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX() - 1, pair.first.getY() + 1)) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX() - 1, pair.first.getY())) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX(), pair.first.getY() - 1)) == 1 && Board::getInstance().getData().count(Coordinate(pair.first.getX() + 1, pair.first.getY() - 1)) == 1)
            {
                winner = PlayerColor::Black;
                return true; // white bee encerclée
            }
        }
    }
    return false;
}

void Match::placeBee()
{
    if (currentplayer == PlayerColor::White)
        WhiteBeePlaced = true;
    else
        BlackBeePlaced = true;
}
Token *Match::getToken_noplaced(TypeInsect t) const
{
    int i = 0;
    if (currentplayer == PlayerColor::White)
    {
        while (i < nbPiece && ((whitetokens[i]->isActive()) || whitetokens[i]->getInsectType() != t))
        {
            i++;
        }
        if (i == nbPiece)
            return nullptr;
        else
            return whitetokens[i];
    }
    else
    {
        while (i < nbPiece && ((blacktokens[i]->isActive()) || blacktokens[i]->getInsectType() != t))
        {
            i++;
        }
        if (i == nbPiece)
            return nullptr;
        else
            return blacktokens[i];
    }
}
vector <Token*> Match::getTokensMovable() const {
    vector <Token*> tokensOnBoard = getActiveTokens(currentplayer);
    vector <Token*>tokensCanMove;
    for (const auto& token : tokensOnBoard)
    {
        if (token->canMove())
        {
            tokensCanMove.insert(tokensCanMove.end(), token);
        }
    }
    return tokensCanMove;



}
void Match::showMovable() const
{
    for (int i = 0; i < getTokensMovable().size(); i++)
    {
        cout << (*getTokensMovable()[i])<< " " << (getTokensMovable()[i]->getID()) << "     ";
    }
    cout << "\n";

}


/*void Hive::Match::undoLastMove(Caretaker& c) {
    if (currentplayer == Hive::PlayerColor::White && whiteUndoCount < 1) {
        //cout << "Vous n'avez plus de retour arrière possible :( \n";
        return;
    }
    else if (currentplayer == Hive::PlayerColor::Black && blackUndoCount < 1) {
        //cout << "Vous n'avez plus de retour arrière possible :( \n";
        return;
    }
    else {
        std::shared_ptr<Hive::Match::Memento> m = c.getLastState(); //on depile et on recup
        if (m != nullptr) {
            RestoreMatchStateFromMemento(m);
            //cout << "match state restored \n" << endl;
        }

        if (currentplayer == Hive::PlayerColor::White) {
            whiteMoveCount--;
        }
        if (currentplayer == Hive::PlayerColor::Black) {
            blackMoveCount--;
        }
    }*/
