#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>
#include "card.h"

class Player : public QObject {
    Q_OBJECT
public:
    enum Type { Human, AI };
    enum Role { Landlord, Farmer };

    explicit Player(QString name, Type type = Human, QObject *parent = nullptr);
    virtual ~Player();

    QString name() const;
    Type type() const;
    Role role() const;
    void setRole(Role role);
    QList<Card*> cards() const;
    void addCard(Card* card);
    void removeCard(Card* card);
    int cardCount() const;

    virtual QList<Card*> play(const QList<Card*>& lastPlay) = 0;

signals:
    void cardsPlayed(const QList<Card*>& cards);
    void passTurn();

protected:
    QString m_name;
    Type m_type;
    Role m_role;
    QList<Card*> m_cards;
};

#endif // PLAYER_H
