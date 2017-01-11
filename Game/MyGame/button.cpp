#include <QBrush>
#include <QGraphicsTextItem>

#include "Button.h"

Button::Button(QString name, QString Color, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    color = Color;
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(Color == "gray")
    {
    brush.setColor(Qt::gray);
    }
    else
    {
        brush.setColor(Qt::green);
    }
    setBrush(brush);

    text = new QGraphicsTextItem(name, this);
    int position_X = rect().width()/2 - text->boundingRect().width()/2;
    int position_Y = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(position_X, position_Y);

    setAcceptHoverEvents(true);
}

void Button::deletingButton()
{
    delete this;
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(color == "gray")
    {
        brush.setColor(Qt::darkGray);
    }
    else
    {
        brush.setColor(Qt::darkGreen);
    }
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(color == "gray")
    {
        brush.setColor(Qt::gray);
    }
    else
    {
        brush.setColor(Qt::green);
    }
    setBrush(brush);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}
