#ifndef MATCH_H_INCLUDED
#define MATCH_H_INCLUDED

#include "Utils.h"
#include "Player.h"
#include "Token.h"
#include "Bee.h"
#include "Spider.h"
#include "Ant.h"
#include "Beetle.h"
#include "GrassHopper.h"
#include "Mosquito.h"
#include "Ladybug.h"
#include "Board.h"
#include <memory>
#include <stack>
#include "MatchMemento.h"
#include "MatchException.h"

#include <QGraphicsScene>
using namespace Hive;

namespace Hive
{
class MatchMemento;

class Match : public QGraphicsScene

{
private:
    /*Token **whitetokens;
        Token **blacktokens;*/
    vector<Token *> whitetokens;
    vector<Token *> blacktokens;
    int nbPiece;
    std::shared_ptr<Player> playerWhite;
    std::shared_ptr<Player> playerBlack;
    PlayerColor currentplayer;
    int blackMoveCount = 0;
    int whiteMoveCount = 0;
    bool WhiteBeePlaced = false;
    bool BlackBeePlaced = false;
    PlayerColor winner = PlayerColor::White;
    // design pattern memento : attribut pile qui stocke les différents objets mementomatch comme des captures d'écran
    // std::stack<MatchMemento> history;
    Token *createToken(PlayerColor color, TypeInsect type, int j);

public:
    Match(const Match &m) = delete;
    Match &operator=(const Match &m) = delete;
    ~Match()
    {
        for (int i = 0; i < nbPiece; i++)
        {
            delete blacktokens[i];
            delete whitetokens[i];
        }
        /* delete[] blacktokens;
             delete[] whitetokens;*/
    }
    Match(std::shared_ptr<Player> white, std::shared_ptr<Player> black, int nb, std::vector<TypeInsect> extension); // ok
    int placeOnBoard(Token *token, const Hive::Coordinate &coord);
    const Player &getCurrentPlayer() const; // ok

    // ajout pour Qt IA
    std::shared_ptr<Player> getPlayerBlackPtr() {return playerBlack;}
    //

    void nextTurn();                        // ok
    bool isFirstMove() const;               // ok
    bool isFourthMove() const;              // ok
    void incrementCounter();                // ok

    int getBlackMoveCount() const { return blackMoveCount; }
    int getWhiteMoveCount() const { return whiteMoveCount; }
    void printhand(PlayerColor c) const;
    vector<Token *> getHand(PlayerColor c) const;
    vector<Token *> getActiveTokens(PlayerColor c) const;

    bool beeNotPlaced() const;
    bool beePlaced(PlayerColor c) const;
    bool verifyPlacement(Token *token, const Coordinate &coord) const;
    bool verifyMoves(Token *token, const Coordinate &coord) const;
    void showPlacements(Token *token) const;

    // void undoLastMove(); // a faire

    bool checkGameOver();
    void placeBee();
    Token *getToken_noplaced(TypeInsect t) const;
    Player &getWinner() const
    {
        if (winner == PlayerColor::White)
            return *playerWhite;
        else
            return *playerBlack;
    }

    vector<Token *> getTokensMovable() const;
    void showMovable() const;


    void printTokenOnBoard(Token* t);
    void displayAllTokens();
    // design pattern memento : méthode qui crée à chaque fois un mementoMatch et l'ajoute dans la pile history
    // void saveState(); // à faire
    //// on va appeler saveState() à chaque placeOnBoard() et tout
};

}
// class MatchMemento
//{
// private:
//     // cette classe va stocker les infos nécessaires pour restaurer l'état du jeu
//     Token **whiteTokensSnap;
//     Token **blackTokensSnap;
//     PlayerColor currentPlayerSnap;
//     int blackMoveCountSnap;
//     int nbPieceSnap;
//     int whiteMoveCountSnap;
//     bool whiteBeePlacedSnap;
//     bool blackBeePlacedSnap;
//     friend class Match;

// public:
//     MatchMemento(Token **whiteTokens, Token **blackTokens, int nbPiece, PlayerColor currentPlayer,
//                  int blackMoveCount, int whiteMoveCount, bool whiteBeePlaced, bool blackBeePlaced) // nb piece sert uniquement pr allouer le tableau
//         : currentPlayerSnap(currentPlayer), nbPieceSnap(nbPiece),
//           blackMoveCountSnap(blackMoveCount),
//           whiteMoveCountSnap(whiteMoveCount),
//           whiteBeePlacedSnap(whiteBeePlaced), blackBeePlacedSnap(blackBeePlaced)
//     {

//        // Allocation et clonage des tokens
//        whiteTokensSnap = new Token *[nbPiece];
//        blackTokensSnap = new Token *[nbPiece];
//        for (int i = 0; i < nbPiece; i++)
//        {
//            whiteTokensSnap[i] = whiteTokens[i]->deepCopy();
//            blackTokensSnap[i] = blackTokens[i]->deepCopy();
//        }
//    }
/*
MatchMemento(const std::vector<Token *> &whiteTokens, const std::vector<Token *> &blackTokens, PlayerColor currentPlayer,
             int blackMoveCount, int whiteMoveCount, bool whiteBeePlaced, bool blackBeePlaced) : whiteTokensSnap(whiteTokens), blackTokensSnap(blackTokens), currentPlayerSnap(currentPlayer), blackMoveCountSnap(blackMoveCount), whiteMoveCountSnap(whiteMoveCount), whiteBeePlacedSnap(whiteBeePlaced), blackBeePlacedSnap(blackBeePlaced) {}
             */
/* ~MatchMemento()
 {
     for (int i = 0; i < nbPieceSnap; i++)
     {
         delete whiteTokensSnap[i];
         delete blackTokensSnap[i];
     }
     delete[] whiteTokensSnap;
     delete[] blackTokensSnap;
 }
};*/

#endif // MATCH_H_INCLUDED

