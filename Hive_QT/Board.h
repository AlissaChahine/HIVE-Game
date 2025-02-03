#ifndef BOARD_H
#define BOARD_H

#include "Utils.h"
#include "Token.h"
#include "Coordinate.h"
using namespace std;
using namespace Hive;

class Board {
    std::map<Coordinate, Token*> data;
    //token est devenu abstract, on est oblig�s d'utiliser des pointeurs dessus

    Board(){};
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

public:
    //methode statique pour obtenir l'instance unique
    static Board& getInstance();

    std::map<Coordinate, Token*>& getData(){ return data; }

    void printBoard() const;
    void showBoard() const; // affichage "graphique"
    vector<Coordinate> getAdjacentTokens(const Coordinate& coord)const;
    bool beehiveIsCompact(map<Coordinate, Token*> data)const;

    vector<Coordinate> getDataAdjacentTokens(const Coordinate& current, map<Coordinate, Token*> board) const;
    void clear() {
        for (int i = 0;i < data.size();i++)
            data.erase(std::prev(data.end()));
    }
    // Réinitialiser le plateau en supprimant tous les tokens
    void reset() { data.clear();}
    void setData(std::map<Coordinate, Token*> mapVersionToRestore) {

        for (auto& pair : data) {
            delete pair.second;
        }
        reset();
        for (const auto& pair : mapVersionToRestore) { // itération sur la map memento
            Coordinate coord = pair.first;   // clé (Coordinate)
            Token* savedToken = pair.second; // valeur (Token*)


            if (savedToken != nullptr) {
                data[coord] = savedToken->deepCopy();
                // Appel à deepCopy()
            }
            else {
                data[coord] = nullptr; // Si le pointeur est nul
            }
        }
        showBoard();


    }
    void showPlacements(Token* token) const; //board
};


#endif // !BOARD_H


