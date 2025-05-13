#include "humanplayer.h"
#include <QApplication> // 添加这一行

HumanPlayer::HumanPlayer(QObject *parent) : Player(parent), m_playConfirmed(false)
{
}

QList<Card*> HumanPlayer::playCards(QList<Card*> lastCards)
{
    m_lastCards = lastCards;
    m_selectedCards.clear();
    m_playConfirmed = false;

    emit requestPlay(lastCards);

    // 等待用户确认出牌
    while (!m_playConfirmed) {
        qApp->processEvents(); // 现在qApp有定义了
    }

    return m_selectedCards;
}

void HumanPlayer::setSelectedCards(const QList<Card*>& cards)
{
    m_selectedCards = cards;
}

void HumanPlayer::confirmPlay()
{
    m_playConfirmed = true;
}
