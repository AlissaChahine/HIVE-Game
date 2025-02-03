#include "vuepartie.h"
#include "ui_vuepartie.h"
#include "Token.h"
#include "Bee.h"
#include "Ant.h"
#include "Spider.h"
#include "Beetle.h"
#include "GrassHopper.h"
#include "Mosquito.h"
#include "Ladybug.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "GameEnd.h"


// Lors de l'ajout des tokens, connectez leurs signaux
void VuePartie::ajouterToken(VueToken *token)
{
    // Connecter le signal du token au slot de VuePartie
    connect(token, SIGNAL(tokenClicked(VueToken*)), this, SLOT(handleTokenClick(VueToken*)));
    token->setTransform(QTransform());
    token->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    token->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, false);
    token->setFlag(QGraphicsItem::ItemIsMovable, false);

    // Ajouter le token à la scène

}
int VuePartie::handleTokenClick(VueToken *token)
{
    for (VueToken * v :vueTokensMatch)
    {
        if (v->tokenPresent())
        {
            if(v->gettoken().getColor()==game.getMatch().getCurrentPlayer().getColor())
            {
                v->setClickable();
            }
            else
            {
                v->setNonClickable();
            }
        }
    }

    if(!(token->isClickable()))
    {
        return 0;
    }

    if (!(token->tokenPresent()))
    {
        Hive::Coordinate coordonee= token->getcoord();
        std::cerr<<coordonee<<endl;

        int i=-1;
        if (tobePlaced==nullptr)
        {
            QMessageBox::critical(nullptr, "Erreur", "nullptr");
        }
        else
        {
            i=game.getMatch().placeOnBoard(tobePlaced,token->getcoord());
        }

        if (i==1)
        {
            if(mainsupp!=nullptr)
            {
                qDebug() << "Scène actuelle de l'élément : erase de la main" << mainsupp->scene();
                qDebug() << "Scène attendue : erase de la main " << boardScene;

                mainsupp->scene()->removeItem(mainsupp);
                vueTokensMatch.erase(std::find(vueTokensMatch.begin(),vueTokensMatch.end(),mainsupp));
            }
            qDebug() << "Scène actuelle de l'élément : erase de l'ancien token pour déplacer " << token->scene();
            qDebug() << "Scène attendue :" << boardScene;

            boardScene->removeItem(token);
            token->setToken(*tobePlaced);
            std::cerr<<tobePlaced->getInsectType()<<game.getMatch().beeNotPlaced()<<tobePlaced->isActive();

            for (auto it = vueTokensMatch.begin(); it != vueTokensMatch.end(); ) {
                if (!(*it)->tokenPresent()) {
                    qDebug() << "Scène actuelle de l'élément : suppression de tous les getpossible" << (*it)->scene();
                    qDebug() << "Scène attendue :" << boardScene;
                    boardScene->removeItem(*it);

                    delete *it; // Libère la mémoire
                    it = vueTokensMatch.erase(it); // Supprime l'élément et récupère le nouvel itérateur
                } else {
                    ++it; // Passe à l'élément suivant uniquement si aucun élément n'est supprimé
                }
            }
            boardScene->addItem(token);


            tobePlaced=nullptr;
            delete mainsupp;
            mainsupp=nullptr;
            nextTurn();
            if(game.getMatch().isFourthMove()&& game.getMatch().beeNotPlaced())
            {
                std::cerr<<game.getMatch().getBlackMoveCount()<<game.getMatch().beeNotPlaced();

                Avertissement();
            }
            else{
                for (VueToken * v :vueTokensMatch)
                {
                    if (v->tokenPresent())
                    {
                        if(v->gettoken().getColor()==game.getMatch().getCurrentPlayer().getColor())
                        {
                            v->setClickable();
                        }
                        else
                        {
                            v->setNonClickable();
                        }
                    }
                }
            }


            //nettoyerJeu();
            //afficherJeu();


            return 1;
        }
        //mainsupp=nullptr;
        return 0;
    }
    if(token->gettoken().isActive() && token->isClickable())
    {
        if (token->gettoken().getPossibleMoves().empty()||token->gettoken().canMove()==false)
        {
            //QMessageBox::critical(nullptr, "Erreur", "Pas de déplacements possibles ! Choisissez une autre pièce ");
            if (game.getMatch().beePlaced(token->gettoken().getColor())==false)
            {
                QMessageBox::information(this, "Erreur", "Pas de déplacements possibles avant de placer la Bee ! ");
            }
            else
            {
                QMessageBox::information(this, "Erreur", "Pas de déplacements possibles ! Choisissez une autre pièce ");
            }
            return -1;
        }
        else {
            tobePlaced=&(token->gettoken());
            if (tobePlaced)
            {
                mainsupp=token;
                //VueToken *nv;
                for (int i=0 ;i<token->gettoken().getPossibleMoves().size();i++)
                {
                    Hive::Coordinate coord=token->gettoken().getPossibleMoves()[i];
                    VueToken *nv=new VueToken(coord);
                    ajouterToken(nv);
                    vueTokensMatch.insert(vueTokensMatch.end(),nv);

                    //nv->updateTextItem();

                    nv->affichageToken();
                    boardScene->addItem(nv);
                    std::cerr<<nv->tokenPresent();

                }
                for (VueToken * v :vueTokensMatch)
                {
                    if (v->tokenPresent())
                        v->setNonClickable();
                    else v->setClickable();
                }
                /*
                for (VueToken * v:vueTokensMatch)
                {
                    if ((v->tokenPresent())==1)
                    {
                        std::cerr<<"efface"<<endl;
                    }
                }*/
            }
            return 1;
        }
        return 0;
    }

    if (token)
    {

        if (!(token->gettoken().isActive()) && token->isClickable())
        {
            mainsupp=token;

            tobePlaced=&(token->gettoken());
            if (tobePlaced)
            {
                std::vector<Hive::Coordinate> coordonee=token->gettoken().getPossiblePlacements();

                for (int i=0 ;i<coordonee.size();i++)
                {

                    Hive::Coordinate coord=token->gettoken().getPossiblePlacements()[i];
                    VueToken *nv=new VueToken(coord);
                    ajouterToken(nv);
                    vueTokensMatch.insert(vueTokensMatch.end(),nv);

                    //nv->updateTextItem();

                    nv->affichageToken();
                    boardScene->addItem(nv);
                    std::cerr<<nv->tokenPresent();

                }
                for (VueToken * v :vueTokensMatch)
                {
                    if (v->tokenPresent())
                        v->setNonClickable();
                    else v->setClickable();
                }

            }
        }
        return 1;
    }
    return 0;
}

VuePartie::VuePartie(QStackedWidget *stackedWidget, QWidget *parent):stackedWidget(stackedWidget), QMainWindow(parent), ui(new Ui::VuePartie), game(Game::getInstance()), vueTokensMatch(nbPiece, nullptr) {

    // a la place de 26 il faudrait init avec le nb de tokens total !
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ffc049;");

    //game.setGameQt(); // fction ajoute dans Game.h
    // qui sera remplacer par les choix du menu etc (pour remplacer setExtension etc)

    // // Créer la scène graphique pour le plateau
    boardScene = new QGraphicsScene(this);
    boardScene->setSceneRect(-600, -600, 1200, 1200);

    //     // Créer la vue graphique pour afficher le plateau
    QGraphicsView *boardView = new QGraphicsView(boardScene, this);
    boardView->setMinimumSize(600, 400); // Taille minimale pour le plateau
    boardView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    boardView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    boardView->centerOn(0,0);
    //boardView->setSceneRect(boardScene->sceneRect());

    //boardView->setFixedHeight(200);
    //boardView->setSceneRect(boardScene->sceneRect());
    //     //boardView->setRenderHint(QPainter::Antialiasing); // pour ameliorer l'esthétique
    //     // Ajouter une couleur de fond pour le plateau
    //boardView->setBackgroundBrush(QBrush(Qt::white));
    boardView->setBackgroundBrush(QColor("#e7dada"));
    // ou : boardView->setStyleSheet("background-color: #ff8849;");

    // Créer les scènes pour les mains
    whiteHandScene = new QGraphicsScene(this);
    blackHandScene = new QGraphicsScene(this);
    // Créer des vues pour afficher les mains
    QGraphicsView *whiteHandView = new QGraphicsView(whiteHandScene, this);
    QGraphicsView *blackHandView = new QGraphicsView(blackHandScene, this);
    whiteHandView->setFixedHeight(150);
    whiteHandView->setFixedWidth(400);
    blackHandView->setFixedHeight(150);
    blackHandView->setFixedWidth(400);
    // Ajouter des labels pour les sections des mains
    QLabel *whiteHandLabel = new QLabel("Main des Blancs", this);
    whiteHandLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");
    QLabel *blackHandLabel = new QLabel("Main des Noirs", this);
    blackHandLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");


    afficherJeu();

    // Créer le layout principal
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Créer un layout vertical pour les mains
    QVBoxLayout *handLayout = new QVBoxLayout();

    QPushButton *pauseButton = new QPushButton("Pause", this);
    pauseButton->setStyleSheet("QPushButton{font-size: 16px;  font-weight: bold; background-color: #ff8849 ;border: 2px solid black;border-radius: 8px;padding: 10px;}"
                               "QPushButton:hover { background-color: #A9A9A9;}");
    // Connecter le bouton Pause à la méthode afficherPause
    connect(pauseButton, &QPushButton::clicked, this, &VuePartie::afficherPause);

    // ajout du label pour afficher le cuurent Player
    curPlayer = new QLabel;
    handLayout->addWidget(curPlayer);
    curPlayer->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");
    curPlayer->setText("Tour du player : " + QString::fromStdString(game.getMatch().getCurrentPlayer().getName()));

    // Ajouter la main des blancs à la colonne des mains
    handLayout->addWidget(whiteHandLabel);
    handLayout->addWidget(whiteHandView);

    // Ajouter la main des noirs à la colonne des mains
    handLayout->addWidget(blackHandLabel);
    handLayout->addWidget(blackHandView);

    mainLayout->addWidget(pauseButton);
    // // Ajouter le plateau à gauche du layout principal
    mainLayout->addWidget(boardView);

    // Ajouter la colonne des mains à droite
    mainLayout->addLayout(handLayout);

    // Appliquer le layout principal à la fenêtre centrale
    setCentralWidget(centralWidget);

    // Ajuster les paramètres de la fenêtre principale
    setWindowTitle("Hive Game");
    resize(800, 600); // Ajuster la taille pour inclure le plateau à gauche et les mains à droite
}

void VuePartie::afficherJeu()
{
    // pour afficher les tokens du match de game
    vector<Token *> activeTokensWhite = game.getMatch().getActiveTokens(PlayerColor::White);
    vector<Token *> activeTokensBlack = game.getMatch().getActiveTokens(PlayerColor::Black);
    vector<Token *> handTokensWhite =  game.getMatch().getHand(PlayerColor::White);
    vector<Token *> handTokensBlack =  game.getMatch().getHand(PlayerColor::Black);

    int iToken = 0;
    for(Token * token : activeTokensWhite)
    {
        vueTokensMatch[iToken] = new VueToken(*token);
        ajouterToken(vueTokensMatch[iToken]);
        iToken++;
    }
    for(Token * token : handTokensWhite)
    {
        vueTokensMatch[iToken] = new VueToken(*token);
        ajouterToken(vueTokensMatch[iToken]);
        iToken++;
    }
    for(Token * token : activeTokensBlack)
    {
        vueTokensMatch[iToken] = new VueToken(*token);
        ajouterToken(vueTokensMatch[iToken]);
        iToken++;
    }
    for(Token * token : handTokensBlack)
    {
        vueTokensMatch[iToken] = new VueToken(*token);
        ajouterToken(vueTokensMatch[iToken]);
        iToken++;
    }
    for (VueToken* vue : vueTokensMatch) {
        if (vue->gettoken().isActive()) {
            // Placer le token à la position de la ligne et colonne
            // vue->affichageToken();
            boardScene->addItem(vue);
        }
    }

    // mains
    // // Variables pour organiser les tokens en ligne (4 par ligne)
    int maxTokensPerRow = 4;  // 4 tokens par ligne
    int xOffsetBlack = 0;  // Décalage horizontal pour les tokens noirs
    int yOffsetBlack = 0;  // Décalage vertical pour les tokens noirs
    int xOffsetWhite = 0;  // Décalage horizontal pour les tokens blancs
    int yOffsetWhite = 0;  // Décalage vertical pour les tokens blancs

    // // Ajouter les tokens inactifs aux bonnes scènes automatiquement en fonction de leur couleur
    //rendre cette partie en fonction pour qu'elle soit appele lors du placement
    for (VueToken* vue : vueTokensMatch) {
        if (!vue->gettoken().isActive()) {
            if (vue->gettoken().getColor() == Hive::PlayerColor::Black) {
                // Placer le token à la position de la ligne et colonne
                vue->setPos(xOffsetBlack * 90, yOffsetBlack * 90);  // 90 px de distance entre chaque token
                blackHandScene->addItem(vue);
                xOffsetBlack++;  // Passer à la colonne suivante
                if (xOffsetBlack >= maxTokensPerRow) {
                    xOffsetBlack = 0;  // Réinitialiser à la première colonne
                    yOffsetBlack++;  // Passer à la ligne suivante
                }
            }
            else if (vue->gettoken().getColor() == Hive::PlayerColor::White) {
                // Placer le token à la position de la ligne et colonne
                vue->setPos(xOffsetWhite * 90, yOffsetWhite * 90);  // 90 px de distance entre chaque token
                whiteHandScene->addItem(vue);
                xOffsetWhite++;  // Passer à la colonne suivante
                if (xOffsetWhite >= maxTokensPerRow) {
                    xOffsetWhite = 0;  // Réinitialiser à la première colonne
                    yOffsetWhite++;  // Passer à la ligne suivante
                }
            }
        }
    }
    //update();
}

void VuePartie::Avertissement()
{
    QMessageBox::critical(nullptr, "Warning", "C'est votre 4ème tour vous devez placer la Bee ");
    for (VueToken *v :vueTokensMatch)
    {
        if (v->gettoken().getColor()==game.getMatch().getCurrentPlayer().getColor() && v->gettoken().getInsectType()==Hive::TypeInsect::Bee )
        {
            v->setClickable();
        }
        else {
            v->setNonClickable();
        }
    }
}


void VuePartie::finishMatch()
{
    Player& winner = game.getMatch().getWinner();
    QMessageBox::information(this, "Finish Match", "Fin du match ! Gagnant-e : " + QString::fromStdString(winner.getName()));

    //afficherPause();
    QWidget *pageend= new GameEnd(stackedWidget);
    stackedWidget->addWidget(pageend);

    stackedWidget->setCurrentIndex(2);
}

void VuePartie::nextTurn()
{
    if(game.getMatch().checkGameOver()==true)
    {
        finishMatch();
    }
    else
    {
        if (game.getMatch().getCurrentPlayer().getIA()==false)
        {
            //QMessageBox::information(this, "Player Turn", "on passe au tour du prochain player");
            game.getMatch().nextTurn();
            if (game.getMatch().getCurrentPlayer().getColor()==PlayerColor::White)
            {
                curPlayer->setText("Tour du player (White) : " + QString::fromStdString(game.getMatch().getCurrentPlayer().getName()));
            }
            else {
                curPlayer->setText("Nv Tour du player (Black) : " + QString::fromStdString(game.getMatch().getCurrentPlayer().getName()));
            }

            if (game.getMatch().getCurrentPlayer().getIA()==true)
            {
                // adapter ia pour placeOnBoard
                //QMessageBox::information(this, "IA Turn", "L'IA va jouer");
                IATurn();
                //QMessageBox::information(this, "IA Turn", "apres IA Turn");
                game.getMatch().nextTurn();
                if(game.getMatch().checkGameOver()==true)
                {
                    finishMatch();
                }
                curPlayer->setText("Tour du player (White) : " + QString::fromStdString(game.getMatch().getCurrentPlayer().getName()));
            }
        }
    }
}


void VuePartie::IATurn(){

    //utilisation de dynamic_pointer_cast pour vérifier et convertir playerBlack en IA
    //std::shared_ptr<IA> iaPlayer = std::dynamic_pointer_cast<IA>(playerBlack);

    std::shared_ptr<IA> iaPlayer = std::dynamic_pointer_cast<IA>(game.getMatch().getPlayerBlackPtr());

    if (iaPlayer) {
        // Appeler la méthode IA_whatToMove() pour choisir un token

        Token* chosenToken = iaPlayer->IA_whatToMove();
        cout << "choix token : " << *chosenToken << endl;
        // Si un token a été choisi, appeler IA_whereToMove() pour choisir la destination
        if (chosenToken) {
            Coordinate chosenMove = iaPlayer->IA_whereToMove(chosenToken);

            //Qt :
            VueToken * tokenIA = new VueToken(chosenMove);
            bool vueFound = false;
            for (VueToken * vue : vueTokensMatch) {
                std::cerr<<"Dans vue : "<<vue->gettoken().getInsectType()<<vue->gettoken().getID()
                <<vue->gettoken().getColor()<<"\n"
                <<"ChosenToken : " << chosenToken->getInsectType()<<chosenToken->getID()
                << chosenToken->getColor()<<"\n";

                // on recherche la vue du Token concerne
                if (vue->gettoken().getInsectType()==chosenToken->getInsectType()
                    && vue->gettoken().getID()==chosenToken->getID()
                    && vue->gettoken().getColor()==chosenToken->getColor())
                {
                    mainsupp = vue; // l'ancienne vue a supprimer
                    vueFound=true;
                    cout << "vue trouve!"<< endl;
                }
            }
            if(!vueFound)
            {
                cout << "vue non trouve"<< endl;
            }

            //
            if(mainsupp!=nullptr)
            {
                if(!(mainsupp->gettoken().isActive()))
                {
                    cout << "non actif"<< endl;
                    mainsupp->scene()->removeItem(mainsupp);
                }
                else {
                    cout << "actif"<< endl;
                    //mainsupp->scene()->removeItem(mainsupp);
                    boardScene->removeItem(mainsupp);
                    //mainsupp->scene()->removeItem(mainsupp);
                    //mainsupp->setVisible(false);
                    //vueTokensMatch.erase(std::find(vueTokensMatch.begin(),vueTokensMatch.end(),mainsupp));
                }
                vueTokensMatch.erase(std::find(vueTokensMatch.begin(),vueTokensMatch.end(),mainsupp));
            }

            int i = game.getMatch().placeOnBoard(chosenToken, chosenMove);
            // Qt :
            if (i==1)
            {
                tobePlaced = chosenToken; // Qt & IA

                // set token aux coord chosenmove
                boardScene->removeItem(tokenIA);
                tokenIA->setToken(*tobePlaced);
                tokenIA->setCoordinate();
                tokenIA->affichageToken();
                std::cerr<<"to be placed by ia : "<<tobePlaced->getInsectType()<<game.getMatch().beeNotPlaced()
                          <<tobePlaced->isActive()
                          <<tobePlaced->getTokenCoordinate()<<endl;

                boardScene->addItem(tokenIA);
                vueTokensMatch.insert(vueTokensMatch.end(),tokenIA);
                tobePlaced=nullptr;
                //delete mainsupp;
                mainsupp=nullptr;
            }
            //mainsupp=nullptr;
        }
    }
    // l'IA a joue
}


void VuePartie::afficherPause() {
    QDialog *pauseDialog = new QDialog(this);
    pauseDialog->setWindowTitle("Pause");
    pauseDialog->setModal(true);
    pauseDialog->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");
    pauseDialog->setFixedSize(400, 300);
    //layout principal de la fenêtre Pause
    QVBoxLayout *dialogLayout = new QVBoxLayout(pauseDialog);

    //ajoute le message "Jeu en pause"
    QLabel *message = new QLabel("Jeu en pause", pauseDialog);
    message->setAlignment(Qt::AlignCenter);
    message->setStyleSheet("font-size: 20px; font-weight: bold;");
    dialogLayout->addWidget(message);

    //ajoute un bouton "Reprendre"
    QPushButton *resumeButton = new QPushButton("Reprendre", pauseDialog);
    resumeButton->setStyleSheet("QPushButton{font-size: 16px;  font-weight: bold; background-color: #90EE90 ;border: 2px solid black;border-radius: 8px;padding: 10px;}"
                                "QPushButton:hover { background-color: #A9A9A9;}");
    dialogLayout->addWidget(resumeButton);

    //ajoute un bouton "Recommencer"
    QPushButton *restartButton = new QPushButton("Recommencer Match", pauseDialog);
    restartButton->setStyleSheet("QPushButton{font-size: 16px;  font-weight: bold; background-color: #DDA0DD ;border: 2px solid black;border-radius: 8px;padding: 10px;}"
                             "QPushButton:hover { background-color: #A9A9A9;}");
    dialogLayout->addWidget(restartButton);

    // Ajoute un bouton "Menu Principal"
    QPushButton *menuButton = new QPushButton("Menu Principal", pauseDialog);
    menuButton->setStyleSheet("QPushButton{font-size: 16px;  font-weight: bold; background-color: #DDA0DD ;border: 2px solid black;border-radius: 8px;padding: 10px;}"
                              "QPushButton:hover { background-color: #A9A9A9;}");

    dialogLayout->addWidget(menuButton);
    //ajoute un bouton "Quitter"
    QPushButton *quitButton = new QPushButton("Quitter", pauseDialog);
    quitButton->setStyleSheet("QPushButton{font-size: 16px;  font-weight: bold; background-color: #f44336 ;border: 2px solid black;border-radius: 8px;padding: 10px;}"
                              "QPushButton:hover { background-color: #A9A9A9;}");
    dialogLayout->addWidget(quitButton);

    //connecte les boutons
    connect(resumeButton, &QPushButton::clicked, pauseDialog, &QDialog::accept); //ferme la fenêtre
    connect(quitButton, &QPushButton::clicked, this, &VuePartie::fermerJeu); //ferme le jeu
    // Accéder à l'instance de `GameEnd`
    GameEnd *gameEnd = dynamic_cast<GameEnd *>(stackedWidget->currentWidget());
    if (gameEnd) {
        connect(restartButton, &QPushButton::clicked, gameEnd, &GameEnd::ReplayMatch); // Rejoue le match
    } else {
        // Si GameEnd n'est pas l'élément actuel, on en crée un
        connect(restartButton, &QPushButton::clicked, [this, pauseDialog]() {
            pauseDialog->accept(); // Ferme la fenêtre Pause
            GameEnd *newGameEnd = new GameEnd(stackedWidget);
            stackedWidget->addWidget(newGameEnd);
            newGameEnd->ReplayMatch();
        });
    }
    connect(menuButton, &QPushButton::clicked, [this, pauseDialog]() {
        pauseDialog->accept();
        GameEnd gameEnd(stackedWidget); // Instancier GameEnd
        gameEnd.RestartGame();          // Appeler RestartGame pour revenir au menu principal
    });

    //affiche la fenêtre Pause
    pauseDialog->exec();
}
void VuePartie::fermerJeu() {
    QApplication::quit();
}

