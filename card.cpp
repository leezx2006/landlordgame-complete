#include "card.h"
#include <QPainter>

Card::Card(Suit suit, Rank rank, QWidget *parent, bool isBack)
    : QWidget(parent), m_suit(suit), m_rank(rank), m_isBack(isBack) {
    setFixedSize(80, 120);
    m_frontImage = QPixmap(imagePath()).scaled(size(), Qt::KeepAspectRatio);
    m_backImage = QPixmap(":/cards/back.png").scaled(size(), Qt::KeepAspectRatio);
}
