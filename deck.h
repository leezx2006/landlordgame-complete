#ifndef DECK_H
#define DECK_H

#include <QVector>
#include "card.h"

class Deck {
public:
    Deck();
    void shuffle();
    QVector<Card> dealCards(int count);
    void reset();

private:
    QVector<Card> m_cards;
};

#endif // DECK_H
