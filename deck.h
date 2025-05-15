#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <QList>
#include "card.h"

class Deck : public QObject
{
    Q_OBJECT
public:
    explicit Deck(QObject *parent = nullptr);
    ~Deck();

    void initialize();
    void shuffle();
    Card* drawCard();
    int cardCount() const { return m_cards.size(); }
    bool isEmpty() const { return m_cards.isEmpty(); }

private:
    QList<Card*> m_cards;
};

#endif // DECK_H
