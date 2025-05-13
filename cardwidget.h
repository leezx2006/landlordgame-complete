#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include "card.h"

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(Card *card, QWidget *parent = nullptr);

    Card* card() const { return m_card; }
    bool isSelected() const { return m_selected; }
    void setSelected(bool selected);

signals:
    void clicked(CardWidget* widget);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Card *m_card;
    bool m_selected;
};

#endif // CARDWIDGET_H
