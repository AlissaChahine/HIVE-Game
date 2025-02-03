#ifndef VUEPARTIE_H
#define VUEPARTIE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "VueToken.h"
#include "Game.h"
#include <QMessageBox>
#include <QPushButton>
#include<QStackedWidget>
#include <QGraphicsItem>
#include "QStackedWidget"
#include "ui_vuepartie.h"

#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class VuePartie;
}
QT_END_NAMESPACE

class VuePartie : public QMainWindow
{
    Q_OBJECT

public:

    VuePartie(QStackedWidget *stackedWidget, QWidget *parent = nullptr);

    ~VuePartie(){
        for (size_t i=0;i<vueTokensMatch.size();i++)
        {
            delete vueTokensMatch[i];
        }
        vueTokensMatch.clear();
        /*
        delete scene;
        delete boardScene;
        delete whiteHandScene;
        delete blackHandScene;
        delete curPlayer;
        delete ui;
        */
    }

    void ajouterToken(VueToken *token);
    void Avertissement();
    void afficherPause();
    void fermerJeu();
    void afficherJeu();
    void finishMatch();
    void nextTurn();
    void IATurn();


private:
    Ui::VuePartie *ui;
    QGraphicsScene *scene; // Déclaration de l'attribut `scene`


    // Hive::Game game;
    Game& game = Game::getInstance();
    size_t nbPiece = game.getVect_extension().size()*2+22;
    std::vector<VueToken*> vueTokensMatch;
    QGraphicsScene *boardScene;
    QGraphicsScene *whiteHandScene;
    QGraphicsScene *blackHandScene;
    QLabel *curPlayer;
    Hive::Token * tobePlaced=nullptr;
    VueToken *mainsupp=nullptr;
    QStackedWidget *stackedWidget;


private slots:
    int handleTokenClick(VueToken *clickedToken);

};

#endif // VUEPARTIE_H
