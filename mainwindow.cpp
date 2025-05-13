#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QRandomGenerator> // 使用Qt6的随机数生成器
#include "cardtypejudger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("斗地主");

    m_deck = new Deck(this);
    m_humanPlayer = new HumanPlayer(this);
    m_aiPlayer1 = new AIPlayer(this);
    m_aiPlayer2 = new AIPlayer(this);

    m_players.append(m_humanPlayer);
    m_players.append(m_aiPlayer1);
    m_players.append(m_aiPlayer2);

    m_currentPlayerIndex = 0;
    m_gameStarted = false;

    // 连接信号槽
    connect(m_humanPlayer, &HumanPlayer::requestPlay, this, [this](QList<Card*> lastCards) {
        Q_UNUSED(lastCards);
        setCurrentPlayer(0);
    });

    // 初始化界面
    updateGameStatus("点击开始游戏");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if (m_gameStarted) {
        QMessageBox::information(this, "游戏中", "游戏已经开始，请继续");
        return;
    }

    initializeGame();
    dealCards();
    m_gameStarted = true;

    // 使用Qt6的随机数生成器替代qrand
    int landlordIndex = QRandomGenerator::global()->bounded(3);
    m_players[landlordIndex]->setLandlord(true);
    updateGameStatus(QString("玩家 %1 成为地主").arg(landlordIndex + 1));

    // 给地主发三张底牌
    for (int i = 0; i < 3; ++i) {
        Card *card = m_deck->drawCard();
        if (card)
            m_players[landlordIndex]->addCard(card);
    }

    // 开始游戏，地主先出牌
    m_currentPlayerIndex = landlordIndex;
    m_lastPlayedCards.clear();
    updatePlayerCardsDisplay();
    updatePlayedCardsDisplay();

    // 如果当前玩家是AI，自动出牌
    if (m_currentPlayerIndex != 0) {
        QTimer::singleShot(1000, this, [this]() {
            QList<Card*> cards = m_players[m_currentPlayerIndex]->playCards(m_lastPlayedCards);
            onPlayerPlayedCards(m_currentPlayerIndex, cards);
        });
    }
}

void MainWindow::on_playButton_clicked()
{
    if (!m_gameStarted || m_currentPlayerIndex != 0)
        return;

    // 获取选中的牌
    QList<Card*> selectedCards;
    for (CardWidget *widget : m_selectedCardWidgets) {
        selectedCards.append(widget->card());
    }

    // 检查牌型是否合法
    CardTypeJudger::CardType type = CardTypeJudger::judgeCardType(selectedCards);
    if (type == CardTypeJudger::Invalid) {
        QMessageBox::warning(this, "出牌错误", "选择的牌型不合法");
        return;
    }

    // 检查是否能大过上一手牌
    if (!m_lastPlayedCards.isEmpty() && !CardTypeJudger::isBetter(selectedCards, m_lastPlayedCards)) {
        QMessageBox::warning(this, "出牌错误", "选择的牌型不能大过上一手牌");
        return;
    }

    // 出牌成功
    onPlayerPlayedCards(0, selectedCards);

    // 清除选中状态
    for (CardWidget *widget : m_selectedCardWidgets) {
        widget->setSelected(false);
    }
    m_selectedCardWidgets.clear();
}

void MainWindow::on_passButton_clicked()
{
    if (!m_gameStarted || m_currentPlayerIndex != 0)
        return;

    // 如果是首轮出牌，不能Pass
    if (m_lastPlayedCards.isEmpty()) {
        QMessageBox::warning(this, "出牌错误", "首轮出牌不能Pass");
        return;
    }

    // Pass
    onPlayerPlayedCards(0, QList<Card*>());
}

void MainWindow::on_cardClicked(CardWidget* widget)
{
    if (!m_gameStarted || m_currentPlayerIndex != 0)
        return;

    // 切换选中状态
    widget->setSelected(!widget->isSelected());

    // 更新选中列表
    if (widget->isSelected()) {
        m_selectedCardWidgets.append(widget);
    } else {
        m_selectedCardWidgets.removeOne(widget);
    }
}

void MainWindow::onLandlordSelected(int playerIndex)
{
    updateGameStatus(QString("玩家 %1 成为地主").arg(playerIndex + 1));
}

void MainWindow::onPlayerPlayedCards(int playerIndex, QList<Card*> cards)
{
    // 显示出牌信息
    QString cardNames;
    if (cards.isEmpty()) {
        cardNames = "Pass";
    } else {
        for (Card *card : cards) {
            cardNames += card->toString() + " ";
        }
    }
    updateGameStatus(QString("玩家 %1 出牌: %2").arg(playerIndex + 1).arg(cardNames));

    // 更新最后出牌
    if (!cards.isEmpty()) {
        m_lastPlayedCards = cards;
    }

    // 从玩家手中移除已出的牌
    if (!cards.isEmpty()) {
        for (Card *card : cards) {
            m_players[playerIndex]->removeCard(card);
        }
    }

    // 检查游戏是否结束
    checkGameOver();
    if (!m_gameStarted) return;

    // 更新界面
    updatePlayerCardsDisplay();
    updatePlayedCardsDisplay();

    // 轮到下一个玩家
    m_currentPlayerIndex = (m_currentPlayerIndex + 1) % 3;

    // 如果当前玩家是AI，自动出牌
    if (m_currentPlayerIndex != 0) {
        QTimer::singleShot(1000, this, [this]() {
            QList<Card*> cards = m_players[m_currentPlayerIndex]->playCards(m_lastPlayedCards);
            onPlayerPlayedCards(m_currentPlayerIndex, cards);
        });
    }
}

void MainWindow::updateGameStatus(const QString& status)
{
    ui->statusLabel->setText(status);
    qDebug() << status;
}

void MainWindow::initializeGame()
{
    // 清空所有玩家的牌
    for (Player *player : m_players) {
        player->clearCards();
        player->setLandlord(false);
    }

    // 初始化牌堆
    m_deck->initialize();
    m_deck->shuffle();

    // 清空出牌区
    m_lastPlayedCards.clear();

    // 清空界面
    for (CardWidget *widget : m_cardWidgets) {
        delete widget;
    }
    m_cardWidgets.clear();
    m_selectedCardWidgets.clear();

    updatePlayerCardsDisplay();
    updatePlayedCardsDisplay();
}

void MainWindow::dealCards()
{
    // 发牌
    for (int i = 0; i < 17; ++i) {
        for (Player *player : m_players) {
            Card *card = m_deck->drawCard();
            if (card)
                player->addCard(card);
        }
    }

    // 显示玩家的牌
    updatePlayerCardsDisplay();
}

void MainWindow::setCurrentPlayer(int playerIndex)
{
    updateGameStatus(QString("轮到玩家 %1 出牌").arg(playerIndex + 1));
}

void MainWindow::updatePlayedCardsDisplay()
{
    // 清空现有出牌显示
    while (ui->playerCardsLayout->count() > 0) {
        QLayoutItem *item = ui->playerCardsLayout->takeAt(0);
        delete item->widget();
        delete item;
    }

    // 显示最后打出的牌
    for (Card *card : m_lastPlayedCards) {
        CardWidget *widget = new CardWidget(card);
        widget->setSelected(false);
        ui->playerCardsLayout->addWidget(widget);
    }
}

void MainWindow::updatePlayerCardsDisplay() {
    // 清空手牌布局
    while (ui->playerHandLayout->count() > 0) {
        QLayoutItem* item = ui->playerHandLayout->takeAt(0);
        delete item->widget();
        delete item;
    }
    m_cardWidgets.clear();
    // 遍历人类玩家手牌，添加到手牌布局
    for (Card* card : m_humanPlayer->cards()) {
        CardWidget* widget = new CardWidget(card);
        ui->playerHandLayout->addWidget(widget); // 改为此布局
        m_cardWidgets.append(widget);
        connect(widget, &CardWidget::clicked, this, &MainWindow::on_cardClicked);
    }
    // 出牌布局仅更新打出的牌（若有）
    updatePlayedCardsDisplay();
}

void MainWindow::checkGameOver()
{
    for (int i = 0; i < m_players.size(); ++i) {
        if (m_players[i]->cardCount() == 0) {
            QString winner = (i == 0) ? "你赢了！" : QString("AI %1 赢了！").arg(i);
            QMessageBox::information(this, "游戏结束", winner);
            m_gameStarted = false;
            return;
        }
    }
}



