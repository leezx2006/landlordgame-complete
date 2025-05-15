#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "deck.h"
#include "humanplayer.h"
#include "aiplayer.h"
#include "cardwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_playButton_clicked();
    void on_passButton_clicked();
    void on_cardClicked(CardWidget* widget);

    void onLandlordSelected(int playerIndex);
    void onPlayerPlayedCards(int playerIndex, QList<Card*> cards);
    void updateGameStatus(const QString& status);

    void on_ai1CardCountLabel_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    Deck *m_deck;
    HumanPlayer *m_humanPlayer;
    AIPlayer *m_aiPlayer1;
    AIPlayer *m_aiPlayer2;
    QList<Player*> m_players;
    QList<CardWidget*> m_cardWidgets;
    QList<CardWidget*> m_selectedCardWidgets;
    QList<Card*> m_lastPlayedCards;
    int m_currentPlayerIndex;
    bool m_gameStarted;
    int m_consecutivePassCount = 0; // 连续Pass次数
    int m_lastPlayerIndex = -1;     // 最后出牌的玩家索引

    void initializeGame();
    void dealCards();
    void setCurrentPlayer(int playerIndex);
    void updatePlayerCardsDisplay();
    void updatePlayedCardsDisplay();
    void checkGameOver();
};
#endif // MAINWINDOW_H
