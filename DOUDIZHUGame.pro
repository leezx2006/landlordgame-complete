QT += core gui widgets multimedia
QT += multimedia
CONFIG += c++17
TARGET = Doudizhu
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    gamecontroller.cpp \
    card.cpp \
    deck.cpp \
    player.cpp \
    aiplayer.cpp \
    audiomanager.cpp \
    cardanimator.cpp

HEADERS += \
    audiomanager.h \
    cardanimator.h \
    gamecontroller.h \
    mainwindow.h \
    gamecontroller.h \
    card.h \
    deck.h \
    player.h \
    aiplayer.h \
    audiomanager.h \
    cardanimator.h \
    cardcombination.h

RESOURCES += \
    resources.qrc

QMAKE_CXXFLAGS += -Wno-deprecated-declarations
