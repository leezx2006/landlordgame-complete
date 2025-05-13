#include "player.h"

Player::Player(QObject *parent) : QObject(parent), m_isLandlord(false)
{
}

void Player::addCard(Card *card)
{
    m_cards.append(card);
    emit cardsChanged();
}

void Player::removeCard(Card *card)
{
    m_cards.removeOne(card);
    emit cardsChanged();
}

void Player::clearCards()
{
    m_cards.clear();
    emit cardsChanged();
}
