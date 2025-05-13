#include "aiplayer.h"
#include "cardtypejudger.h"
#include <algorithm>

AIPlayer::AIPlayer(QObject *parent) : Player(parent)
{
}

QList<Card*> AIPlayer::playCards(QList<Card*> lastCards)
{
    return findBestCardsToPlay(lastCards);
}

QList<Card*> AIPlayer::findBestCardsToPlay(QList<Card*> lastCards)
{
    if (lastCards.isEmpty()) {
        // 首轮出牌，选择最小的单牌
        return findSmallestSingle();
    }

    // 检查是否有炸弹或王炸
    QList<Card*> bomb = findBomb();
    if (!bomb.isEmpty() && CardTypeJudger::isBetter(bomb, lastCards)) {
        return bomb;
    }

    QList<Card*> rocket = findRocket();
    if (!rocket.isEmpty()) {
        return rocket;
    }

    // 根据牌型选择最佳出牌
    CardTypeJudger::CardType lastType = CardTypeJudger::judgeCardType(lastCards);

    switch (lastType) {
    case CardTypeJudger::Single: {
        QList<Card*> largerSingle = findLargerSingle(lastCards);
        if (!largerSingle.isEmpty()) {
            return largerSingle;
        }
        // 没有更大的单牌，出最小单牌
        return findSmallestSingle();
    }
    case CardTypeJudger::Pair: {
        QList<Card*> largerPair = findLargerPair(lastCards);
        if (!largerPair.isEmpty()) {
            return largerPair;
        }
        // 没有更大的对子，出最小对子（若有）
        return findSmallestPair();
    }
    // 其他牌型处理...
    default:
        break;
    }

    // 若所有牌型都无法应对，出最小单牌（可根据需求扩展其他牌型）
    return findSmallestSingle();
}

QList<Card*> AIPlayer::findSmallestSingle()
{
    if (m_cards.isEmpty()) return QList<Card*>();

    Card *smallest = m_cards.first();
    for (Card *card : m_cards) {
        if (card->rank() < smallest->rank()) {
            smallest = card;
        }
    }

    return QList<Card*>() << smallest;
}

QList<Card*> AIPlayer::findBomb()
{
    QList<Card*> sortedCards = m_cards;
    std::sort(sortedCards.begin(), sortedCards.end(), [](Card* a, Card* b) {
        return a->rank() < b->rank();
    });

    for (int i = 0; i <= sortedCards.size() - 4; ++i) {
        if (sortedCards[i]->rank() == sortedCards[i+1]->rank() &&
            sortedCards[i]->rank() == sortedCards[i+2]->rank() &&
            sortedCards[i]->rank() == sortedCards[i+3]->rank()) {
            return QList<Card*>() << sortedCards[i] << sortedCards[i+1] << sortedCards[i+2] << sortedCards[i+3];
        }
    }

    return QList<Card*>();
}

QList<Card*> AIPlayer::findRocket()
{
    bool hasSmallJoker = false;
    bool hasBigJoker = false;

    for (Card *card : m_cards) {
        if (card->rank() == Card::SmallJoker) hasSmallJoker = true;
        if (card->rank() == Card::BigJoker) hasBigJoker = true;
    }

    if (hasSmallJoker && hasBigJoker) {
        return QList<Card*>()
        << new Card(Card::Joker, Card::BigJoker)
        << new Card(Card::Joker, Card::SmallJoker);
    }

    return QList<Card*>();
}

QList<Card*> AIPlayer::findLargerSingle(const QList<Card*>& lastCards)
{
    if (lastCards.isEmpty()) return QList<Card*>();

    Card *lastCard = lastCards.first();
    Card *bestCard = nullptr;

    for (Card *card : m_cards) {
        if (card->rank() > lastCard->rank()) {
            if (!bestCard || card->rank() < bestCard->rank()) {
                bestCard = card;
            }
        }
    }

    if (bestCard) {
        return QList<Card*>() << bestCard;
    }

    return QList<Card*>();
}

QList<Card*> AIPlayer::findLargerPair(const QList<Card*>& lastCards)
{
    if (lastCards.size() != 2 || lastCards.first()->rank() != lastCards.last()->rank()) {
        return QList<Card*>();
    }

    int lastRank = lastCards.first()->rank();
    QList<Card*> pairs;

    for (int i = 0; i < m_cards.size() - 1; ++i) {
        for (int j = i + 1; j < m_cards.size(); ++j) {
            if (m_cards[i]->rank() == m_cards[j]->rank() && m_cards[i]->rank() > lastRank) {
                pairs << m_cards[i] << m_cards[j];
                return pairs; // 找到第一个对子就返回
            }
        }
    }

    return QList<Card*>();
}

// 新增：找最小对子
QList<Card*> AIPlayer::findSmallestPair()
{
    if (m_cards.size() < 2) return QList<Card*>();

    QList<Card*> sortedCards = m_cards;
    std::sort(sortedCards.begin(), sortedCards.end(), [](Card* a, Card* b) {
        return a->rank() < b->rank();
    });

    for (int i = 0; i < sortedCards.size() - 1; ++i) {
        if (sortedCards[i]->rank() == sortedCards[i + 1]->rank()) {
            return QList<Card*>() << sortedCards[i] << sortedCards[i + 1];
        }
    }

    return QList<Card*>();
}
