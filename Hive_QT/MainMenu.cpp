#include "MainMenu.h"
#include "qstackedwidget.h"
#include "vuepartie.h"
#include <QVBoxLayout>
#include <QLabel>
#include "vuepartie.h"
#include <QMessageBox>
#include "Game.h"
#include "QStackedWidget"
#include "GameEnd.h"

MainMenu::MainMenu(QStackedWidget *stackedWidget, QWidget *parent) : QMainWindow(parent), game(Game::getInstance())
    ,stackedWidget(stackedWidget) {
    // Set up UI elements
    setWindowTitle("Hive Game");
    resize(800, 600);
    this->setStyleSheet("background-color: #ffc049;");


    QLabel *welcomeLabel = new QLabel("WELCOME", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);  // Center-align the text
    welcomeLabel->setStyleSheet("font-size: 34px; font-weight: bold; color: darkblue;");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(welcomeLabel);  //

    QLabel *playerTypeLabel = new QLabel("Choose player type:");
    playerTypeLabel->setAlignment(Qt::AlignCenter);
    playerTypeLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");
    QVBoxLayout *twoPlayerLayout = new QVBoxLayout();
    QVBoxLayout *aiPlayerLayout = new QVBoxLayout();
    QHBoxLayout *playerTypeLayout = new QHBoxLayout();  // Horizontal layout for buttons

    twoPlayerButton = new QPushButton("Two Players",this);
    aiPlayerButton = new QPushButton("Player vs AI",this);
    twoPlayerButton->setFixedSize(120, 40);
    aiPlayerButton->setFixedSize(120, 40);
    twoPlayerLayout->addWidget(twoPlayerButton);
    aiPlayerLayout->addWidget(aiPlayerButton);
    playerTypeLayout->setAlignment(Qt::AlignCenter);
    // difficutly
    QLabel *difficultyLabel = new QLabel("Choose level",this);
    difficultyLabel->setAlignment(Qt::AlignCenter);  // Center-align the text
    easyButton = new QPushButton("Easy",this);
    hardButton = new QPushButton("Hard",this);

    playerInput = new QLineEdit(this);

    playerInput->setPlaceholderText("enter player name");
    playerInput->setFixedSize(200, 40);
    playerInput->setStyleSheet("background-color: white;color:darkblue; font-size: 14px; border: 2px solid black;border-radius: 8px;padding: 10px;");

    easyButton ->setFixedSize(120,40);
    hardButton ->setFixedSize(120,40);
    difficultyLabel->setStyleSheet("font-size: 18px; color: darkblue;");
    difficultyLabel->hide();
    easyButton->hide();
    hardButton->hide();

    playerInput->hide();

    // player names
    player1Input = new QLineEdit(this);
    player2Input = new QLineEdit(this);
    player1Input->setPlaceholderText("Enter Player 1 Name");
    player2Input->setPlaceholderText("Enter Player 2 Name");
    player1Input->setFixedSize(200, 40);
    player2Input->setFixedSize(200, 40);
    player1Input->setStyleSheet("background-color: white;color:darkblue; font-size: 14px; border: 2px solid black;border-radius: 8px;padding: 10px;");
    player2Input->setStyleSheet("background-color: white;color:darkblue; font-size: 14px; border: 2px solid black;border-radius: 8px;padding: 10px;");

    player1Input->hide();
    player2Input->hide();

    layout->addWidget(difficultyLabel);
    aiPlayerLayout->addWidget(hardButton);

    aiPlayerLayout->addWidget(playerInput);

    aiPlayerLayout->addWidget(easyButton);
    twoPlayerLayout->addWidget(player1Input);
    twoPlayerLayout->addWidget(player2Input);
    playerTypeLayout->addLayout(twoPlayerLayout);
    playerTypeLayout->addLayout(aiPlayerLayout);
    layout->addWidget(playerTypeLabel);
    layout->addLayout(playerTypeLayout);


    QLabel *extensionLabel = new QLabel("What extension would you like ?");
    extensionLabel->setAlignment(Qt::AlignCenter);  // Center-align the text
    extensionLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");
    QHBoxLayout *noneLayout = new QHBoxLayout();  // Horizontal layout for buttons
    QHBoxLayout *extensionLayout = new QHBoxLayout();  // Horizontal layout for buttons
    QHBoxLayout *bothLayout = new QHBoxLayout();  // Horizontal layout for buttons

    noneButton = new QPushButton("None",this);
    bothButton = new QPushButton("Both",this);
    ladybugButton = new QPushButton("Ladybug Extension",this);
    mosquitoButton = new QPushButton("Mosquito Extension",this);

    noneLayout->addWidget(noneButton);
    noneLayout->setAlignment(Qt::AlignCenter);
    extensionLayout->addWidget(ladybugButton);
    extensionLayout->addWidget(mosquitoButton);
    extensionLayout->setAlignment(Qt::AlignCenter);
    bothLayout->addWidget(bothButton);
    bothLayout->setAlignment(Qt::AlignCenter);

    layout->addWidget(extensionLabel);
    layout->addLayout(noneLayout);
    layout->addLayout(extensionLayout);
    layout->addLayout(bothLayout);

    // QString buttonStyle = "QPushButton {"
    //                       "    font-size: 16px;"

    //                       "    font-weight: bold;"
    //                       "    background-color: #ff8849;"
    //                       "    border: 2px solid black;"
    //                       "    border-radius: 8px;"
    //                       "    padding: 10px;"
    //                       "}"
    //                       "QPushButton:hover {"
    //                       "    background-color: #A9A9A9;"
    //                       "}"
    //                       "QPushButton:pressed {"
    //                       "    font-size: 18px;"
    //                       "    font-weight: bold;"
    //                       "    background-color: darkblue;"
    //                       "    border: 2px solid black;"
    //                       "    border-radius: 8px;"
    //                       "    padding: 10px;"
    //                       "}";


    QHBoxLayout *startLayout= new QHBoxLayout();

    startButton = new QPushButton("Start Game");
    startButton->setFixedSize(200, 60);

    startLayout -> setAlignment(Qt::AlignCenter);
    startLayout ->addWidget(startButton);
    layout -> addLayout(startLayout);



    setButtonStyle(twoPlayerButton, "normal");
    setButtonStyle(aiPlayerButton, "normal");
    setButtonStyle(easyButton,"normal");
    setButtonStyle(hardButton,"normal");
    setButtonStyle(ladybugButton, "normal");
    setButtonStyle(mosquitoButton, "normal");
    setButtonStyle(noneButton,"normal");
    setButtonStyle(bothButton,"normal");
    setButtonStyle(startButton, "pre-selected");


    setCentralWidget(centralWidget);

    // connexions
    connect(startButton, &QPushButton::clicked, this, &MainMenu::startGame);
    connect(twoPlayerButton, &QPushButton::clicked, this, &MainMenu::onTwoPlayerSelected);
    connect(aiPlayerButton, &QPushButton::clicked, this, &MainMenu::onAISelected);
    connect(ladybugButton, &QPushButton::clicked, this, &MainMenu::onLadyBugSelected);
    connect(mosquitoButton, &QPushButton::clicked, this, &MainMenu::onMosquitoSelected);
    connect(noneButton, &QPushButton::clicked, this, &MainMenu::onNoneSelected);
    connect(bothButton, &QPushButton::clicked, this, &MainMenu::onBothSelected);

    connect(easyButton, &QPushButton::clicked, this, &MainMenu::onEasySelected);
    connect(hardButton, &QPushButton::clicked, this, &MainMenu::onHardSelected);

    //connect(this,&MainMenu::startSignal,this,&MainMenu::starttestMatch)
    //     connect(twoPlayerButton, &QPushButton::clicked, this, [aiPlayerButton, difficultyLabel, easyButton, hardButton, twoPlayerButton]() {

}

void MainMenu::setButtonStyle(QPushButton *button, const QString &state) {
    if (state == "normal") {
        button->setStyleSheet("QPushButton {font-size: 16px;  font-weight: bold; background-color: #ff8849 ;border: 2px solid black;border-radius: 8px;padding: 10px;} QPushButton:hover { background-color: #A9A9A9;} QPushButton:selected { background-color: darkblue;}");
    } else if (state == "selected") {
        button->setStyleSheet("QPushButton {font-size: 16px;  font-weight: bold; background-color: darkblue ;border: 2px solid black;border-radius: 8px;padding: 10px;} QPushButton:hover { background-color: #A9A9A9;}");
    }
    else if (state == "pre-selected") {
        button->setStyleSheet("QPushButton {font-size: 16px;  font-weight: bold; background-color: lightgreen ;border: 2px solid black;border-radius: 8px;padding: 10px;} QPushButton:hover { background-color: #A9A9A9;}");
    }
    else if (state == "disabled") {
        button->setStyleSheet("QPushButton {font-size: 16px;  font-weight: bold; background-color: #A9A9A9 ;border: 2px solid black;border-radius: 8px;padding: 10px;}");
    }
}

void MainMenu::onTwoPlayerSelected() {
    setButtonStyle(twoPlayerButton, "pre-selected");
    setButtonStyle(aiPlayerButton, "disabled");
    easyButton->hide();  // Hide level selection buttons
    hardButton->hide();

    playerInput->hide();

    player1Input->show();
    player2Input->show();
    qDebug() << "Two Player selected";
}
void MainMenu::onAISelected() {
    setButtonStyle(twoPlayerButton, "disabled");
    setButtonStyle(aiPlayerButton, "pre-selected");
    easyButton->show();  // Hide level selection buttons
    hardButton->show();

    playerInput->show();

    player1Input ->hide();
    player2Input->hide();
    easyButton->setParent(aiPlayerButton->parentWidget());
    // easyButton->move(aiPlayerButton->x(), aiPlayerButton->y() + aiPlayerButton->height() + 12);
    //hardButton->move(easyButton->x()+easyButton->width()+12, easyButton->y());

    qDebug() << "AI selected";

}

void MainMenu::onHardSelected() {
    setButtonStyle(hardButton, "selected");
    setButtonStyle(easyButton,"disabled");

}
void MainMenu::onEasySelected() {
    setButtonStyle(easyButton, "selected");
    setButtonStyle(hardButton,"disabled");
}

void MainMenu::onLadyBugSelected() {
    setButtonStyle(ladybugButton, "selected");
    setButtonStyle(noneButton, "disabled");
    setButtonStyle(mosquitoButton, "disabled");
    setButtonStyle(bothButton, "disabled");

}
void MainMenu::onMosquitoSelected() {
    setButtonStyle(mosquitoButton, "selected");
    setButtonStyle(ladybugButton, "disabled");
    setButtonStyle(noneButton, "disabled");
    setButtonStyle(bothButton, "disabled");

}

void MainMenu::onNoneSelected() {
    setButtonStyle(ladybugButton, "disabled");
    setButtonStyle(mosquitoButton, "disabled");
    setButtonStyle(bothButton, "disabled");
    setButtonStyle(noneButton, "selected");

}
void MainMenu::onBothSelected() {
    setButtonStyle(ladybugButton, "disabled");
    setButtonStyle(mosquitoButton, "disabled");
    setButtonStyle(noneButton, "disabled");
    setButtonStyle(bothButton, "selected");
}

// void MainMenu::starttestMatch(){
//     //game.startMatch();
//     GameThread *gameThread = new GameThread();
//     gameThread->start();
//     //QMessageBox::information(this, "Game Start", "The game has started!");
//     // gameWindow->show();
//     // this->hide();
//     emit matchReady(game);
// }

void MainMenu::startGame() {

    if (aiPlayerButton->styleSheet().contains("lightgreen") && hardButton->styleSheet().contains("darkblue")) {
        game.setPlayerIA(2);
        game.setPlayerNames(playerInput->text().toStdString(),"IA Player");
        qDebug() << "Starting game with AI level 2.";
    } else if (aiPlayerButton->styleSheet().contains("lightgreen") && easyButton->styleSheet().contains("darkblue")) {
        game.setPlayerIA(1);
        if(playerInput->text()=="")
        {
            player1Input->setText("Player White (You)");
        }
        game.setPlayerNames(playerInput->text().toStdString(),"IA Player");
        qDebug() << "Starting game with AI level 1.";
    }
    else //if(twoPlayerButton->styleSheet().contains("darkblue"))
    {
        if(player1Input->text()=="" && player2Input->text()=="")
        {
            player1Input->setText("Player White");
            player2Input->setText("Player Black");
        }
        game.setPlayerNames(player1Input->text().toStdString(), player2Input->text().toStdString());
        qDebug() << "Starting game with Two Players: " << player1Input->text() << " and " << player2Input->text();
    }

    // Set extensions
    //pour avoir un match par defaut avec 0 extensions :
    if (mosquitoButton->styleSheet().contains("darkblue")) {
        game.setExtension(2);
    } else if (bothButton->styleSheet().contains("darkblue"))
    {
        game.setExtension(3);
    }
    else //if (ladybugButton->styleSheet().contains("darkblue"))
    {
        game.setExtension(1);
    }

    game.startMatch();

    //emit startJeu(&game.getMatch());
    //qDebug() << "match initialized creating VuePartie..." ;

    // passer le QStackedWidget en argument pour pvr l'utiliser dans les fcts
    QWidget *pageMatch = new VuePartie(stackedWidget);

    stackedWidget->addWidget(pageMatch);
    QWidget *pageEnd = new GameEnd(stackedWidget);
    stackedWidget->addWidget(pageEnd);

    QMessageBox::information(this, "Game Start", "The game has started!");

    stackedWidget->setCurrentIndex(1);
}
