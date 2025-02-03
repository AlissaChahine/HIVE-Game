#include "vuepartie.h"
#include <QApplication>
#include "VueToken.h"
#include <QGraphicsView>
#include <iostream>

#include "Game.h"

#include <QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "MainMenu.h"

int pagesHive(int argc, char*argv[]){

    QApplication app(argc, argv);

    // Crée le QStackedWidget et ajoute les pages
    QStackedWidget *stackedWidget = new QStackedWidget;

    // Crée les widgets pour chaque page
    QWidget *pageMenu = new MainMenu(stackedWidget);

    // dans MainMenu :
    //QWidget *pageMatch = new VuePartie;
    //stackedWidget->addWidget(pageMatch);

    stackedWidget->addWidget(pageMenu);

    // Layout principal
    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addWidget(stackedWidget);

    QWidget mainWidgetTest;
    mainWidgetTest.setLayout(layoutMain);
    mainWidgetTest.setWindowTitle("Hive Game");
    mainWidgetTest.resize(400, 300);

    // Affiche l'interface
    mainWidgetTest.show();

    return app.exec();
}

int main(int argc,char*argv[]) {
    int res = pagesHive(argc, argv);
    return res;
}
