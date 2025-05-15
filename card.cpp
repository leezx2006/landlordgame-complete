#include "card.h"

Card::Card(Suit suit, Rank rank, QObject *parent) : QObject(parent), m_suit(suit), m_rank(rank)
{
}

QString Card::suitString() const
{
    switch (m_suit) {
    case Spade: return "Spade";
    case Heart: return "Heart";
    case Club: return "Club";
    case Diamond: return "Diamond";
    case Joker: return "Joker";
    default: return "";
    }
}

QString Card::rankString() const
{
    switch (m_rank) {
    case Three: return "3";
    case Four: return "4";
    case Five: return "5";
    case Six: return "6";
    case Seven: return "7";
    case Eight: return "8";
    case Nine: return "9";
    case Ten: return "10";
    case Jack: return "J";
    case Queen: return "Q";
    case King: return "K";
    case Ace: return "A";
    case Two: return "2";
    case SmallJoker: return "Small Joker";
    case BigJoker: return "Big Joker";
    default: return "";
    }
}

QString Card::toString() const
{
    if (m_suit == Joker)
        return rankString();
    else
        return suitString() + " " + rankString();
}
