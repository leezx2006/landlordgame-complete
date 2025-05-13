#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onCardClicked();
    void updateGameUI();

private:
    void setupUI();
    GameController *m_controller;
    // ...其他成员变量...
};

#endif // MAINWINDOW_H
