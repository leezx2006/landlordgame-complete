#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>
#include "card.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void addCard(Card *card);
    void removeCard(Card *card);
    void clearCards();

    QList<Card*> cards() const { return m_cards; }
    int cardCount() const { return m_cards.size(); }

    bool hasCards() const { return !m_cards.isEmpty(); }
    bool isLandlord() const { return m_isLandlord; }
    void setLandlord(bool landlord) { m_isLandlord = landlord; }

    virtual QList<Card*> playCards(QList<Card*> lastCards) = 0;

signals:
    void cardsChanged();

protected:
    QList<Card*> m_cards;
    bool m_isLandlord;
};

#endif // PLAYER_H
