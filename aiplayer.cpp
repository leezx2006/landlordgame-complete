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

QList<Card*> AIPlayer::findBestCardsToPlay(QList<Card*> lastCards) {
    if (lastCards.isEmpty()) {
        // 首轮必须出牌，出最小单牌（规则要求，若需允许首轮Pass可改为返回空列表）
        return findSmallestSingle();
    }

    // 优先检查炸弹/王炸（仅当能覆盖时出牌）
    QList<Card*> bomb = findBomb();
    if (!bomb.isEmpty() && CardTypeJudger::isBetter(bomb, lastCards)) {
        return bomb;
    }
    QList<Card*> rocket = findRocket();
    if (!rocket.isEmpty()) { // 王炸可覆盖任意牌型，直接返回
        return rocket;
    }

    // 处理不同牌型的覆盖逻辑
    CardTypeJudger::CardType lastType = CardTypeJudger::judgeCardType(lastCards);
    switch (lastType) {
    case CardTypeJudger::Single: {
        // 找更大的单牌，否则Pass
        return findLargerSingle(lastCards);
    }
    case CardTypeJudger::Pair: {
        // 找更大的对子，否则Pass
        return findLargerPair(lastCards);
    }
    // 新增：处理三不带、三带一、三带二、顺子等牌型（均无法覆盖，直接Pass）
    case CardTypeJudger::Triple:
    case CardTypeJudger::TripleOne:
    case CardTypeJudger::TripleTwo:
    case CardTypeJudger::Straight:
        return QList<Card*>(); // 非单牌/对子/炸弹时，无法覆盖，直接Pass
    default:
        return QList<Card*>(); // 未知牌型Pass
    }
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

QList<Card*> AIPlayer::findRocket() {
    Card* smallJoker = nullptr;
    Card* bigJoker = nullptr;
    // 遍历手牌查找大小王实例
    for (Card* card : m_cards) {
        if (card->rank() == Card::SmallJoker) smallJoker = card;
        if (card->rank() == Card::BigJoker) bigJoker = card;
    }
    // 同时存在时返回实际对象
    if (smallJoker && bigJoker) {
        return {bigJoker, smallJoker}; // 王炸顺序通常为大鬼+小鬼
    }
    return QList<Card*>();
}



QList<Card*> AIPlayer::findLargerSingle(const QList<Card*>& lastCards) {
    if (lastCards.isEmpty()) return QList<Card*>();
    Card *lastCard = lastCards.first();
    Card *bestCard = nullptr;
    // 遍历手牌找最小的更大单牌（确保出最小的有效牌，避免出更大的牌浪费）
    for (Card *card : m_cards) {
        if (card->rank() > lastCard->rank()) {
            if (!bestCard || card->rank() < bestCard->rank()) { // 找最小的更大单牌
                bestCard = card;
            }
        }
    }
    return bestCard ? QList<Card*>() << bestCard : QList<Card*>(); // 找不到则返回空
}

QList<Card*> AIPlayer::findLargerPair(const QList<Card*>& lastCards) {
    if (lastCards.size() != 2 || lastCards.first()->rank() != lastCards.last()->rank()) {
        return QList<Card*>();
    }
    int lastRank = lastCards.first()->rank();
    QList<Card*> pairs;
    // 找最小的更大对子
    for (int i = 0; i < m_cards.size() - 1; ++i) {
        for (int j = i + 1; j < m_cards.size(); ++j) {
            if (m_cards[i]->rank() == m_cards[j]->rank() && m_cards[i]->rank() > lastRank) {
                // 按顺序找第一个最小的更大对子（确保出最小有效牌）
                return {m_cards[i], m_cards[j]};
            }
        }
    }
    return QList<Card*>(); // 找不到则返回空
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
