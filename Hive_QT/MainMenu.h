#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include "Game.h"
#include "qstackedwidget.h"

class MainMenu : public QMainWindow {
    Q_OBJECT

public:
    explicit MainMenu(QStackedWidget *stackedWidget, QWidget *parent = nullptr);
    // passer le QStackedWidget en argument pour pvr l'utiliser dans les fcts
    // et ça fctionne pas si on laisse ca en non comment :
    //explicit MainMenu(QWidget *parent = nullptr);

private:
    QPushButton *startButton;  // To start the game
    QPushButton *twoPlayerButton;
    QPushButton *aiPlayerButton;
    QPushButton *easyButton;
    QPushButton *noneButton;
    QPushButton *bothButton;
    QPushButton *hardButton;
    QPushButton *ladybugButton;
    QPushButton *mosquitoButton;
    QLineEdit *player1Input;
    QLineEdit *player2Input;
    QLineEdit * playerInput;

    Game& game = Game::getInstance();
    void setButtonStyle(QPushButton *button, const QString &state);

    QStackedWidget *stackedWidget;

public slots:
    void startGame();  // Slot to start the game
    void onTwoPlayerSelected();
    void onAISelected();
    void onHardSelected();
    void onEasySelected();
    void onLadyBugSelected();
    void onMosquitoSelected();
    void onNoneSelected();
    void onBothSelected();

    // void startgame();

};

#endif // MAINMENU_H
