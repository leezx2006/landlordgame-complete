#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QPixmap>

class Card : public QWidget {
    Q_OBJECT
public:
    enum Suit { Spade, Heart, Club, Diamond, Joker };
    enum Rank { Three=3, Four, Five, Six, Seven, Eight, Nine, Ten,
                Jack, Queen, King, Ace, Two, SmallJoker, BigJoker };

    explicit Card(Suit suit, Rank rank, QWidget *parent = nullptr, bool isBack = false);

    QPixmap getImage() const;
    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;

    Suit suit() const { return m_suit; }
    Rank rank() const { return m_rank; }
    bool isJoker() const { return m_suit == Joker; }
    void flip();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Suit m_suit;
    Rank m_rank;
    bool m_isBack;
    QPixmap m_frontImage;
    QPixmap m_backImage;
    QString imagePath() const;
};

#endif // CARD_H
