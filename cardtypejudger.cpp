#include "cardtypejudger.h"
#include <QMap>

CardTypeJudger::CardType CardTypeJudger::judgeCardType(const QList<Card*>& cards)
{
    int size = cards.size();

    if (size == 0) return Invalid;

    // 王炸
    if (size == 2) {
        bool hasSmallJoker = false;
        bool hasBigJoker = false;
        for (Card *card : cards) {
            if (card->rank() == Card::SmallJoker) hasSmallJoker = true;
            if (card->rank() == Card::BigJoker) hasBigJoker = true;
        }
        if (hasSmallJoker && hasBigJoker) return Rocket;
    }

    // 炸弹
    if (size == 4) {
        int rank = cards.first()->rank();
        bool allSame = true;
        for (Card *card : cards) {
            if (card->rank() != rank) {
                allSame = false;
                break;
            }
        }
        if (allSame) return Bomb;
    }

    // 统计每种点数的牌的数量
    QMap<int, int> rankCount;
    for (Card *card : cards) {
        rankCount[card->rank()]++;
    }

    // 单牌
    if (size == 1) return Single;

    // 对子
    if (size == 2 && rankCount.size() == 1 && rankCount.first() == 2) return Pair;

    // 三不带
    if (size == 3 && rankCount.size() == 1 && rankCount.first() == 3) return Triple;

    // 三带一
    if (size == 4 && rankCount.size() == 2) {
        bool hasThree = false;
        bool hasOne = false;
        for (auto count : rankCount) {
            if (count == 3) hasThree = true;
            if (count == 1) hasOne = true;
        }
        if (hasThree && hasOne) return TripleOne;
    }

    // 三带二
    if (size == 5 && rankCount.size() == 2) {
        bool hasThree = false;
        bool hasTwo = false;
        for (auto count : rankCount) {
            if (count == 3) hasThree = true;
            if (count == 2) hasTwo = true;
        }
        if (hasThree && hasTwo) return TripleTwo;
    }

    // 顺子
    if (size >= 5 && size <= 12) {
        QList<int> ranks;
        for (Card *card : cards) {
            ranks.append(card->rank());
        }
        std::sort(ranks.begin(), ranks.end());

        // 检查是否连续
        bool isStraight = true;
        for (int i = 1; i < ranks.size(); ++i) {
            if (ranks[i] != ranks[i-1] + 1) {
                isStraight = false;
                break;
            }
        }

        // 不能包含大小王
        if (isStraight && !ranks.contains(Card::SmallJoker) && !ranks.contains(Card::BigJoker)) {
            return Straight;
        }
    }

    return Invalid;
}

bool CardTypeJudger::isBetter(const QList<Card*>& cardsA, const QList<Card*>& cardsB)
{
    CardType typeA = judgeCardType(cardsA);
    CardType typeB = judgeCardType(cardsB);

    // 王炸最大
    if (typeA == Rocket) return true;
    if (typeB == Rocket) return false;

    // 炸弹比非炸弹大
    if (typeA == Bomb && typeB != Bomb) return true;
    if (typeB == Bomb && typeA != Bomb) return false;

    // 同类型比较
    if (typeA == typeB) {
        if (typeA == Single || typeA == Pair || typeA == Triple) {
            return cardsA.first()->rank() > cardsB.first()->rank();
        }
        if (typeA == Straight) {
            // 比较第一张牌的大小
            QList<int> ranksA, ranksB;
            for (Card *card : cardsA) ranksA.append(card->rank());
            for (Card *card : cardsB) ranksB.append(card->rank());
            std::sort(ranksA.begin(), ranksA.end());
            std::sort(ranksB.begin(), ranksB.end());
            return ranksA.first() > ranksB.first();
        }
        if (typeA == Bomb) {
            return cardsA.first()->rank() > cardsB.first()->rank();
        }
    }

    return false;
}
