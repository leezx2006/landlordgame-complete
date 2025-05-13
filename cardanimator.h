#ifndef CARDANIMATOR_H
#define CARDANIMATOR_H

#include <QObject>
#include <QPropertyAnimation>

class CardWidget;

class CardAnimator : public QObject {
    Q_OBJECT
public:
    enum AnimationType { MoveTo, Flip, Scale };
    static CardAnimator* instance();
    void animate(CardWidget* target, AnimationType type, const QVariant& endValue, int duration = 500);

private:
    explicit CardAnimator(QObject *parent = nullptr);
};

#endif // CARDANIMATOR_H
