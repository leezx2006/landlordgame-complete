#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
    Q_OBJECT
public:
    explicit AIPlayer(QObject *parent = nullptr);
    void makeDecision(const QVector<Card>& lastPlay, bool isNewRound) override;

private:
         // AI决策逻辑...
};

#endif // AIPLAYER_H
```
