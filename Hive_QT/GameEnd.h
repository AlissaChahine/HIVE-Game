
#ifndef GameEnd_H
#define GameEnd_H

#include <QMainWindow>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include "Game.h"
#include "QStackedWidget"

class GameEnd : public QMainWindow {
    Q_OBJECT

public:
    explicit GameEnd(QStackedWidget *stackedWidget, QWidget *parent = nullptr);
    ~GameEnd(){
        delete RestartButton;
        delete ReplayButton;
        delete QuitButton;}

private:
    QPushButton *RestartButton;  // To start the game
    QPushButton *ReplayButton;
    QPushButton *QuitButton;

    Game& game = Game::getInstance();
    Match& match= game.getMatch();
    void setButtonStyle(QPushButton *button, const QString &state);
    QStackedWidget *stackedWidget;


public slots:
    void RestartGame();  // Slot to start the game
    void ReplayMatch();
    void QuitGame();
    void showPage();
};

#endif // GameEnd_H
