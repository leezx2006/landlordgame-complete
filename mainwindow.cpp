#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_controller(new GameController(this)) {
    setupUI();
    connect(m_controller, &GameController::gameStarted, this, &MainWindow::updateGameUI);
    m_controller->startNewGame();
}

void MainWindow::setupUI() {
    // 创建游戏界面布局
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 添加卡牌显示区域
    QHBoxLayout *cardLayout = new QHBoxLayout;
    mainLayout->addLayout(cardLayout);
    // ...初始化卡牌显示...

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    resize(800, 600);
}
