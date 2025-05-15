#include "cardwidget.h"
#include <QPainter>
#include <QPixmap>

CardWidget::CardWidget(Card *card, QWidget *parent) : QWidget(parent), m_card(card), m_selected(false)
{
    setFixedSize(80, 120);
}

void CardWidget::setSelected(bool selected)
{
    if (m_selected != selected) {
        m_selected = selected;
        update();
    }
}

void CardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制卡片背景
    QRect cardRect(0, 0, width(), height());
    painter.fillRect(cardRect, Qt::white);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(cardRect);

    // 绘制选中状态
    if (m_selected) {
        painter.fillRect(cardRect.adjusted(2, 2, -2, -2), QColor(220, 230, 255));
    }

    // 绘制卡牌信息
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(cardRect, Qt::AlignCenter, m_card->rankString());

    // 根据花色设置颜色
    QColor suitColor;
    switch (m_card->suit()) {
    case Card::Spade:
    case Card::Club:
        suitColor = Qt::black;
        break;
    case Card::Heart:
    case Card::Diamond:
        suitColor = Qt::red;
        break;
    case Card::Joker:
        suitColor = Qt::blue;
        break;
    }

    painter.setPen(suitColor);
    painter.drawText(cardRect.adjusted(5, 5, -5, -5), Qt::AlignTop | Qt::AlignLeft, m_card->suitString());
}

void CardWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(this);
}
