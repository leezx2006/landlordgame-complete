#ifndef CARDLAYOUT_H
#define CARDLAYOUT_H

#include <QLayout>
#include <QList>
#include <QRect>
#include "cardwidget.h"

class CardLayout : public QLayout
{
public:
    enum Orientation {
        Horizontal,
        Vertical
    };

    explicit CardLayout(Orientation orientation, QWidget *parent = nullptr);
    ~CardLayout();

    void addItem(QLayoutItem *item) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    void setGeometry(const QRect &rect) override;

private:
    QList<QLayoutItem*> m_items;
    Orientation m_orientation;
    int m_spacing;
};

#endif // CARDLAYOUT_H
