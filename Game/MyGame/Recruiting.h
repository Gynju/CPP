#ifndef RECRUITING_H
#define RECRUITING_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "Button.h"

class Recruiting: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Recruiting(QString Variant);
    int recruitTime;

    bool buttonsExist = false;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void updateIcon();
    QString variant;

public slots:
    void recruit();
    void changeButtonStatus();

private:
    int cost[3] = {0,0,0};

};
#endif // RECRUITING_H
