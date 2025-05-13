#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player
{
    Q_OBJECT
public:
    explicit AIPlayer(QObject *parent = nullptr);

    QList<Card*> playCards(QList<Card*> lastCards) override;

private:
    QList<Card*> findBestCardsToPlay(QList<Card*> lastCards);
    QList<Card*> findSmallestSingle();
    QList<Card*> findBomb();
    QList<Card*> findRocket();
    QList<Card*> findLargerSingle(const QList<Card*>& lastCards);
    QList<Card*> findLargerPair(const QList<Card*>& lastCards);
     QList<Card*> findSmallestPair();
};

#endif // AIPLAYER_H
