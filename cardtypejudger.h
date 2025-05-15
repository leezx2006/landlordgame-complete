#ifndef CARDTYPEJUDGER_H
#define CARDTYPEJUDGER_H

#include <QList>
#include "card.h"

class CardTypeJudger
{
public:
    enum CardType {
        Invalid,
        Single,
        Pair,
        Triple,
        TripleOne,
        TripleTwo,
        Straight,
        Bomb,
        Rocket
    };

    static CardType judgeCardType(const QList<Card*>& cards);
    static bool isBetter(const QList<Card*>& cardsA, const QList<Card*>& cardsB);
};

#endif // CARDTYPEJUDGER_H
