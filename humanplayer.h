#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player
{
    Q_OBJECT
public:
    explicit HumanPlayer(QObject *parent = nullptr);

    QList<Card*> playCards(QList<Card*> lastCards) override;

signals:
    void requestPlay(QList<Card*> lastCards);

public slots:
    void setSelectedCards(const QList<Card*>& cards);
    void confirmPlay();

private:
    QList<Card*> m_selectedCards;
    QList<Card*> m_lastCards;
    bool m_playConfirmed;
};

#endif // HUMANPLAYER_H
