#include "deck.h"
#include <QRandomGenerator>

Deck::Deck(QObject *parent) : QObject(parent)
{
}

Deck::~Deck()
{
    qDeleteAll(m_cards);
}

void Deck::initialize()
{
    qDeleteAll(m_cards);
    m_cards.clear();

    // 添加普通牌
    for (int s = 0; s < 4; ++s) {
        for (int r = 3; r <= 15; ++r) {
            m_cards.append(new Card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r)));
        }
    }

    // 添加大小王
    m_cards.append(new Card(Card::Joker, Card::SmallJoker));
    m_cards.append(new Card(Card::Joker, Card::BigJoker));
}

void Deck::shuffle()
{
    for (int i = 0; i < m_cards.size() - 1; ++i) {
        int j = QRandomGenerator::global()->bounded(i, m_cards.size());
        m_cards.swapItemsAt(i, j);
    }
}

Card* Deck::drawCard()
{
    if (m_cards.isEmpty())
        return nullptr;

    return m_cards.takeFirst();
}
