QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Ant.cpp \
    Bee.cpp \
    Board.cpp \
    Game.cpp \
    Beetle.cpp \
    GameEnd.cpp \
    Ladybug.cpp \
    MainMenu.cpp \
    Match.cpp \
    Mosquito.cpp \
    Spider.cpp \
    Token.cpp \
    IA.cpp \
    Grasshopper.cpp \
    VueToken.cpp \
    mainQT.cpp \
    vuepartie.cpp
    MainMenu.cpp


HEADERS +=  \
Ant.h \
Bee.h \
Board.h \
Game.h \
Beetle.h \
    GameEnd.h \
Ladybug.h \
    MainMenu.h \
Match.h \
Mosquito.h \
Spider.h \
Token.h \
IA.h \
Grasshopper.h \
MatchException.h \
GameException.h \
Utils.h \
Player.h \
Coordinate.h \
VueToken.h \
vuepartie.h
MainMenu.h


FORMS += \
 vuepartie.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
