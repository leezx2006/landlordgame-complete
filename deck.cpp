#include "deck.h"
#include <QRandomGenerator>

Deck::Deck() { reset(); }

void Deck::reset() {
    m_cards.clear();
    // 生成牌堆逻辑...
}

// 实现其他成员函数...

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "card.h"

      class Player : public QObject {
    Q_OBJECT
public:
    enum Type { Human, AI };
    enum Role { Landlord, Farmer };

    explicit Player(QObject *parent = nullptr, Type type = Human);

    virtual void makeDecision(const QVector<Card>& lastPlay, bool isNewRound) = 0;
    void receiveCards(const QVector<Card>& cards);
    void playCards(const QVector<Card>& cards);

    // ...其他成员函数...

signals:
    void played(const QVector<Card>& cards);
    void passed();

protected:
    QVector<Card> m_handCards;
    Role m_role = Farmer;
    Type m_type;
};

#endif // PLAYER_H
