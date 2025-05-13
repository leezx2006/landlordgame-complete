#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "player.h"
#include "deck.h"

class GameController : public QObject {
    Q_OBJECT
public:
    enum GameState { Dealing, Bidding, Playing, Ended };

    explicit GameController(QObject *parent = nullptr);
    void startNewGame();
    void processPlay(const QVector<Card>& cards);

    // ...其他成员函数...

signals:
    void gameStateChanged(GameState state);
    void cardsDealt();
    void playValidated(bool valid);
    void gameEnded(bool landlordWin);
    void gameStarted();
private:
    Deck m_deck;
    QVector<Player*> m_players;
    GameState m_state;
    // ...其他成员变量...
};

#endif // GAMECONTROLLER_H
