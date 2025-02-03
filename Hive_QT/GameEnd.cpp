#include "GameEnd.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "qapplication.h"
#include "qgraphicsview.h"
#include "vuepartie.h"
#include <QMessageBox>
#include "Game.h"
#include "QStackedWidget"
#include "MainMenu.h"
#include "VuePartie.h"


GameEnd::GameEnd(QStackedWidget *stackedWidget,QWidget *parent) : QMainWindow(parent), game(Game::getInstance()),stackedWidget(stackedWidget) {
    // Set up UI elements
    setWindowTitle("Hive Game");
    resize(800, 600);
    this->setStyleSheet("background-color: #ffc049;");



    QLabel *endLabel = new QLabel("End of the game !", this);
    endLabel->setAlignment(Qt::AlignCenter);  // Center-align the text
    endLabel->setStyleSheet("font-size: 34px; font-weight: bold; color: darkblue;");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(endLabel);  //

    QLabel *choiceendLabel = new QLabel("Would you like to ...");
    choiceendLabel->setAlignment(Qt::AlignCenter);
    choiceendLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: darkblue;");
    QVBoxLayout *choiceendLayout = new QVBoxLayout();
    ReplayButton = new QPushButton("Replay a match",this);
    RestartButton = new QPushButton("Restart the game",this);
    QuitButton = new QPushButton("Qui the game",this);
    ReplayButton->setFixedSize(200,60);
    RestartButton->setFixedSize(200,60);
    QuitButton->setFixedSize(200,60);
    choiceendLayout->addWidget(ReplayButton);
    choiceendLayout->addWidget(RestartButton);
    choiceendLayout->addWidget(QuitButton);
    choiceendLayout->setAlignment(Qt::AlignCenter);
    layout->addWidget(choiceendLabel);
    layout->addLayout(choiceendLayout);


    setButtonStyle(RestartButton,"normal");
    setButtonStyle(ReplayButton,"normal");
    setButtonStyle(QuitButton,"normal");
    setCentralWidget(centralWidget);

    // connexions
    connect(RestartButton, &QPushButton::clicked, this, &GameEnd::RestartGame);
    connect(ReplayButton, &QPushButton::clicked, this, &GameEnd::ReplayMatch);
    connect(QuitButton, &QPushButton::clicked, this, &GameEnd::QuitGame);

}
void GameEnd::setButtonStyle(QPushButton *button, const QString &state) {
    if (state == "normal") {
        button->setStyleSheet("QPushButton {font-size: 16px;  font-weight: bold; background-color: #ff8849 ;border: 2px solid black;border-radius: 8px;padding: 10px;} QPushButton:hover { background-color: #A9A9A9;} QPushButton:selected { background-color: darkblue;}");
    } else if (state == "selected") {
        button->setStyleSheet("QPushButton {font-size: 16px;  font-weight: bold; background-color: darkblue ;border: 2px solid black;border-radius: 8px;padding: 10px;} QPushButton:hover { background-color: #A9A9A9;}");
    }
}

void GameEnd::RestartGame() {
    setButtonStyle(ReplayButton, "selected");
    game.deleteMatch();
    // vider stack widget et le re init
    for(int i = stackedWidget->count(); i >= 0; i--)
    {
        QWidget* widget = stackedWidget->widget(i);
        stackedWidget->removeWidget(widget);
        if (widget!=nullptr && stackedWidget->indexOf(widget) != -1 && widget != this)
        {
            delete widget;}
    }
    QWidget *pageMenu = new MainMenu(stackedWidget);

    stackedWidget->addWidget(pageMenu);
    stackedWidget->setCurrentIndex(0);

}

void GameEnd::ReplayMatch(){
    setButtonStyle(ReplayButton, "selected");
    game.deleteMatch();
    Board::getInstance().clear();
    std::cerr<<"board clear";
    game.startMatch();
    std::cerr<<"debut match";

    // retirer l'ancien vuepartie du stack et le menu de fin
    for (int i = stackedWidget->count() - 1; i >= 1; i--)
    {
        QWidget* widget = stackedWidget->widget(i);
        stackedWidget->removeWidget(widget);

        if (widget!=nullptr && stackedWidget->indexOf(widget) != -1 && widget != this)
        {
            std::cerr<<"delete";
            delete widget;}
    }
    std::cerr<<"delete ancienne partie";

    QWidget* pageMatch = new VuePartie(stackedWidget);
    stackedWidget->addWidget(pageMatch);
    if (stackedWidget->indexOf(this) == -1)
        stackedWidget->addWidget(this);
    stackedWidget->setCurrentIndex(1);
    std::cerr<<"new partie";
}

void GameEnd::QuitGame(){
    setButtonStyle(QuitButton, "selected");
    game.deleteMatch();
    QMessageBox::information(this, "Game end","thanks for playing ! bye <3");

    std::cerr<<"delte widget";
    QApplication::quit();
}

/*
 * // fonctionne aussi :
void GameEnd::QuitGame(){
    setButtonStyle(QuitButton, "selected");
    game.deleteMatch();
    for (int i = stackedWidget->count() - 1; i >= 0; i--) {
        QWidget* widget = stackedWidget->widget(i);
        stackedWidget->removeWidget(widget);
        if (widget != nullptr && stackedWidget->indexOf(widget) == -1 && widget != this) {
            delete widget;
        }
    }
    QMessageBox::information(this, "Game end","thanks for playing ! bye <3");
    // supprime le widget juste avant de quitter
    this->deleteLater();
    QApplication::quit();
}
*/

void GameEnd::showPage() {
    this->show();
}

