#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QString>

class Card : public QObject
{
    Q_OBJECT
public:
    enum Suit {
        Spade, Heart, Club, Diamond, Joker
    };

    enum Rank {
        Three = 3, Four, Five, Six, Seven, Eight, Nine, Ten,
        Jack, Queen, King, Ace, Two, SmallJoker = 16, BigJoker = 17
    };

    explicit Card(Suit suit, Rank rank, QObject *parent = nullptr);

    Suit suit() const { return m_suit; }
    Rank rank() const { return m_rank; }

    QString suitString() const;
    QString rankString() const;
    QString toString() const;

private:
    Suit m_suit;
    Rank m_rank;
};

#endif // CARD_H
