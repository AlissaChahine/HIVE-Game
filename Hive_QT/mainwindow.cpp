#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include "VueToken.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::VuePartie) {
    ui->setupUi(this);

    // Créer la scène graphique pour le plateau
    QGraphicsScene *boardScene = new QGraphicsScene(this);


    //Ajouter un rectangle de fond pour le plateau
    // QGraphicsRectItem *background = new QGraphicsRectItem(-200, -200, 400, 400);
    // background->setBrush(QBrush(Qt::lightGray));
    // background->setPen(QPen(Qt::black));
    // boardScene->addItem(background);

    // Créer la vue graphique pour afficher le plateau
    QGraphicsView *boardView = new QGraphicsView(boardScene, this);
    boardView->setMinimumSize(600, 600); // Taille minimale pour le plateau
    // boardView->setSceneRect(boardScene->sceneRect());
    // boardView->setRenderHint(QPainter::Antialiasing); // pour ameliorer l'esthétique

    // Ajouter une couleur de fond pour le plateau
    boardView->setBackgroundBrush(QBrush(Qt::lightGray));

    // Créer des tokens et les ajouter au plateau
    Token* d1 = new Ant(Hive::PlayerColor::White, 2);
    d1->setCoordinate(0, -3);
    d1->setActive();
    Token* d2 = new Spider(Hive::PlayerColor::White, 2);
    d2->setCoordinate(1, -3);
    d2->setActive();
    VueToken * vue1=new VueToken(*d1);
    VueToken * vue2=new VueToken(*d2);

    //     Token* d3 = new Beetle(Hive::PlayerColor::Black, 2);
    //     d3->setCoordinate(-1, -2);
    //     d3->setActive();
    //     Token* d4 = new Bee(Hive::PlayerColor::Black, 2);
    //     d4->setCoordinate(0, -2);
    //     d4->setActive();
    //     Token* d5 = new Grasshopper(Hive::PlayerColor::Black, 2);
    //     d5->setCoordinate(1, -2);
    //     d5->setActive();
    //     Token* d6 = new Ant(Hive::PlayerColor::Black, 2);
    //     d6->setCoordinate(-2, -1);
    //     d6->setActive();
    //     Token* d7 = new Ant(Hive::PlayerColor::Black, 2);
    //     d7->setCoordinate(-1, -1);
    //     d7->setActive();
    //     Token* d8 = new Beetle(Hive::PlayerColor::White, 2);
    //     d8->setCoordinate(0, -1);
    //     d8->setActive();
    //     Token* d9 = new Grasshopper(Hive::PlayerColor::Black, 2);
    //     d9->setCoordinate(-2, 0);
    //     d9->setActive();
    //     Token* d10 = new Spider(Hive::PlayerColor::White, 2);
    //     d10->setCoordinate(0, 0);
    //     d10->setActive();
    //     Token* d11 = new Ant(Hive::PlayerColor::White, 2);
    //     d11->setCoordinate(1, 0);
    //     d11->setActive();
    //     Token* d12 = new Spider(Hive::PlayerColor::Black, 2);
    //     d12->setCoordinate(-3, 1);
    //     d12->setActive();
    //     Token* d13 = new Spider(Hive::PlayerColor::Black, 2);
    //     d13->setCoordinate(-2, 1);
    //     d13->setActive();
    //     Token* d14 = new Beetle(Hive::PlayerColor::Black, 2);
    //     d14->setCoordinate(-1, 1);
    //     d14->setActive();
    //     Token* d15 = new Beetle(Hive::PlayerColor::White, 2);
    //     d15->setCoordinate(1, 1);
    //     d15->setActive();
    //     Token* d16 = new Beetle(Hive::PlayerColor::Black, 2);
    //     d16->setCoordinate(-2, 2);
    //     d16->setActive();
    //     Token* d17 = new Spider(Hive::PlayerColor::Black, 2);
    //     d17->setCoordinate(-1, 2);
    //     d17->setActive();
    //     Token* d18 = new Bee(Hive::PlayerColor::White, 2);
    //     d18->setCoordinate(0, 2);
    //     d18->setActive();
    //     Token* d19 = new Spider(Hive::PlayerColor::Black, 2);
    //     d19->setCoordinate(1, 2);
    //     d19->setActive();

    //     // Liste des tokens actifs à ajouter
    std::vector<VueToken*> activeTokens = {vue1, vue2};

    // Ajouter les tokens actif a la scene du plateau automatiquement en fonction de leur couleur
    for (VueToken* vue : activeTokens) {
        if (vue->gettoken().isActive()) {
            // Placer le token à la position de la ligne et colonne
            vue->setPos((vue->gettoken().getTokenCoordinate().getX() * 80)
                            + (vue->gettoken().getTokenCoordinate().getY() * 40)
                        , vue->gettoken().getTokenCoordinate().getY() * 60);
            boardScene->addItem(vue);
        }
    }

    // >>>>>>> b1296fc655cd5499edded47f64d31c984a3f20f9

    // Créer les scènes pour les mains
    QGraphicsScene *whiteHandScene = new QGraphicsScene(this);
    QGraphicsScene *blackHandScene = new QGraphicsScene(this);

    // Créer des vues pour afficher les mains
    QGraphicsView *whiteHandView = new QGraphicsView(whiteHandScene, this);
    QGraphicsView *blackHandView = new QGraphicsView(blackHandScene, this);

    whiteHandView->setFixedHeight(150);
    blackHandView->setFixedHeight(150);

    // Ajouter des labels pour les sections des mains
    QLabel *whiteHandLabel = new QLabel("Main des Blancs", this);
    QLabel *blackHandLabel = new QLabel("Main des Noirs", this);

    // // Créer des tokens inactifs pour la main des Blancs et des Noirs
    Token* b3 = new Mosquito(Hive::PlayerColor::Black, 2); // Token non actif
    Token* b4 = new Grasshopper(Hive::PlayerColor::White, 2); // Token non actif
    Token* a2 = new Ant(Hive::PlayerColor::White, 2); // Token non actif

    VueToken * vue3=new VueToken(*b3);
    VueToken * vue4=new VueToken(*b4);
    VueToken * vue5=new VueToken(*a2);

    // // Liste des tokens inactifs à ajouter
    std::vector<VueToken*> inactiveTokens = {vue3, vue4, vue5};

    // // Variables pour organiser les tokens en ligne (4 par ligne)
    int maxTokensPerRow = 4;  // 4 tokens par ligne
    int xOffsetBlack = 0;  // Décalage horizontal pour les tokens noirs
    int yOffsetBlack = 0;  // Décalage vertical pour les tokens noirs
    int xOffsetWhite = 0;  // Décalage horizontal pour les tokens blancs
    int yOffsetWhite = 0;  // Décalage vertical pour les tokens blancs

    // // Ajouter les tokens inactifs aux bonnes scènes automatiquement en fonction de leur couleur
    for (VueToken* vue : inactiveTokens) {
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

    // Créer le layout principal
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Créer un layout vertical pour les mains
    QVBoxLayout *handLayout = new QVBoxLayout();

    // Ajouter la main des blancs à la colonne des mains
    handLayout->addWidget(whiteHandLabel);
    handLayout->addWidget(whiteHandView);

    // Ajouter la main des noirs à la colonne des mains
    handLayout->addWidget(blackHandLabel);
    handLayout->addWidget(blackHandView);

    // // Ajouter le plateau à gauche du layout principal
    mainLayout->addWidget(boardView);

    // Ajouter la colonne des mains à droite
    mainLayout->addLayout(handLayout);

    // Appliquer le layout principal à la fenêtre centrale
    setCentralWidget(centralWidget);

    // Ajuster les paramètres de la fenêtre principale
    setWindowTitle("Hive Game");
    resize(1000, 600); // Ajuster la taille pour inclure le plateau à gauche et les mains à droite
    // delete b3;
    // delete b4;
    // delete a2;
}

MainWindow::~MainWindow() {
    delete ui;
}
