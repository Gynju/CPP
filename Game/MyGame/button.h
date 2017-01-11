#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Button(QString name, QString Color, QGraphicsItem* parent=NULL);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QString color;

public slots:
    void deletingButton();

private:
    QGraphicsTextItem* text;

signals:
    void clicked();
};

#endif // BUTTON_H
