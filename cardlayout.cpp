#include "cardlayout.h"

CardLayout::CardLayout(Orientation orientation, QWidget *parent) : QLayout(parent), m_orientation(orientation), m_spacing(5)
{
}

CardLayout::~CardLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void CardLayout::addItem(QLayoutItem *item)
{
    m_items.append(item);
}

int CardLayout::count() const
{
    return m_items.size();
}

QLayoutItem *CardLayout::itemAt(int index) const
{
    return m_items.value(index);
}

QLayoutItem *CardLayout::takeAt(int index)
{
    if (index >= 0 && index < m_items.size())
        return m_items.takeAt(index);
    return nullptr;
}

QSize CardLayout::sizeHint() const
{
    return minimumSize();
}

QSize CardLayout::minimumSize() const
{
    if (m_items.isEmpty())
        return QSize();

    QSize minSize;
    if (m_orientation == Horizontal) {
        int totalWidth = 0;
        int maxHeight = 0;
        for (int i = 0; i < m_items.size(); ++i) {
            totalWidth += m_items[i]->minimumSize().width();
            if (i > 0)
                totalWidth -= m_spacing; // 重叠部分
            maxHeight = qMax(maxHeight, m_items[i]->minimumSize().height());
        }
        minSize = QSize(totalWidth, maxHeight);
    } else {
        int totalHeight = 0;
        int maxWidth = 0;
        for (int i = 0; i < m_items.size(); ++i) {
            totalHeight += m_items[i]->minimumSize().height();
            if (i > 0)
                totalHeight -= m_spacing; // 重叠部分
            maxWidth = qMax(maxWidth, m_items[i]->minimumSize().width());
        }
        minSize = QSize(maxWidth, totalHeight);
    }

    return minSize;
}

void CardLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    if (m_items.isEmpty())
        return;

    if (m_orientation == Horizontal) {
        int x = rect.x();
        for (int i = 0; i < m_items.size(); ++i) {
            QLayoutItem *item = m_items[i];
            QSize size = item->sizeHint();
            item->setGeometry(QRect(x, rect.y(), size.width(), size.height()));
            x += size.width() - m_spacing; // 每张牌重叠一部分
        }
    } else {
        int y = rect.y();
        for (int i = 0; i < m_items.size(); ++i) {
            QLayoutItem *item = m_items[i];
            QSize size = item->sizeHint();
            item->setGeometry(QRect(rect.x(), y, size.width(), size.height()));
            y += size.height() - m_spacing; // 每张牌重叠一部分
        }
    }
}
