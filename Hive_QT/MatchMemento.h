#ifndef MATCHMEMENTO_H_INCLUDED
#define MATCHMEMENTO_H_INCLUDED

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
/*
***************************************************NE SERA PLUS UTILISE****************************************************
namespace Hive
{

    class MatchMemento
    {
    private:
        std::vector<Token *> whiteTokensSnap;
        std::vector<Token *> blackTokensSnap;
        PlayerColor currentPlayerSnap;
        int blackMoveCountSnap;
        int whiteMoveCountSnap;
        bool whiteBeePlacedSnap;
        bool blackBeePlacedSnap;
        int nbPieceSnap;

        // Constructeur privé accessible uniquement par Match
        MatchMemento(const std::vector<Token *> &whiteTokens, const std::vector<Token *> &blackTokens, int nbpiece,
                     PlayerColor currentPlayer, int blackMoveCount, int whiteMoveCount,
                     bool whiteBeePlaced, bool blackBeePlaced)
            : currentPlayerSnap(currentPlayer),
              blackMoveCountSnap(blackMoveCount),
              whiteMoveCountSnap(whiteMoveCount),
              whiteBeePlacedSnap(whiteBeePlaced),
              blackBeePlacedSnap(blackBeePlaced),
              nbPieceSnap(nbpiece)
        {

            // Clone profond des tokens
            for (const auto &token : whiteTokens)
            {

                whiteTokensSnap.push_back(token->deepCopy());
            }
            for (const auto &token : blackTokens)
            {
                blackTokensSnap.push_back(token->deepCopy());
            }
        }

    public:
        ~MatchMemento()
        {
            for (auto token : whiteTokensSnap)
                delete token;
            for (auto token : blackTokensSnap)
                delete token;
        }

        friend class Match;
    };

}
*/
/*
class MatchMemento
{
private:
    // cette classe va stocker les infos nécessaires pour restaurer l'état du jeu
    Token **whiteTokensSnap;
    Token **blackTokensSnap;
    PlayerColor currentPlayerSnap;
    int blackMoveCountSnap;
    int nbPieceSnap;
    int whiteMoveCountSnap;
    bool whiteBeePlacedSnap;
    bool blackBeePlacedSnap;
    friend class Match;

public:
    MatchMemento(Token **whiteTokens, Token **blackTokens, int nbPiece, PlayerColor currentPlayer,
                 int blackMoveCount, int whiteMoveCount, bool whiteBeePlaced, bool blackBeePlaced) // nb piece sert uniquement pr allouer le tableau
        : currentPlayerSnap(currentPlayer), nbPieceSnap(nbPiece),
          blackMoveCountSnap(blackMoveCount),
          whiteMoveCountSnap(whiteMoveCount),
          whiteBeePlacedSnap(whiteBeePlaced), blackBeePlacedSnap(blackBeePlaced)
    {

        // Allocation et clonage des tokens
        whiteTokensSnap = new Token *[nbPiece];
        blackTokensSnap = new Token *[nbPiece];
        for (int i = 0; i < nbPiece; i++)
        {
            whiteTokensSnap[i] = whiteTokens[i]->deepCopy();
            blackTokensSnap[i] = blackTokens[i]->deepCopy();
        }
    }

    MatchMemento(const std::vector<Token *> &whiteTokens, const std::vector<Token *> &blackTokens, PlayerColor currentPlayer,
                 int blackMoveCount, int whiteMoveCount, bool whiteBeePlaced, bool blackBeePlaced) : whiteTokensSnap(whiteTokens), blackTokensSnap(blackTokens), currentPlayerSnap(currentPlayer), blackMoveCountSnap(blackMoveCount), whiteMoveCountSnap(whiteMoveCount), whiteBeePlacedSnap(whiteBeePlaced), blackBeePlacedSnap(blackBeePlaced) {}

    ~MatchMemento()
    {
        for (int i = 0; i < nbPieceSnap; i++)
        {
            delete whiteTokensSnap[i];
            delete blackTokensSnap[i];
        }
        delete[] whiteTokensSnap;
        delete[] blackTokensSnap;
    }
};
*/
#endif // MATCHMEMENTO_H_INCLUDED
