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
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void updateIcon();

    int recruit_time;

    QString variant;

public slots:
    void changeButtonStatus();
    void recruit();


private:
    int cost[3] = {0,0,0};

};
#endif // RECRUITING_H
