#pragma once

#include <QGraphicsLineItem>

class DiagramItem;

// Arrow inherits QGraphicsLineItem and is an arrow that connect two DiagramItems.

/*
The Arrow class is a graphics item that connects two DiagramItems. It draws an arrow head to one of the items.
To achieve this the item needs to paint itself and also re implement methods used by the graphics scene to check for collisions and selections.
The class inherits QGraphicsLine item, and draws the arrowhead and moves with the items it connects.
*/

class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    Arrow(DiagramItem* startItem, DiagramItem* endItem, QGraphicsItem* parent = nullptr);

    [[nodiscard]] int type() const override { return Type; }
    // boundingRect() and shape() are reimplemented from QGraphicsLineItem and are used by the scene to check for collisions and selections.
    [[nodiscard]] QRectF boundingRect() const override;
    [[nodiscard]] QPainterPath shape() const override;
    // The item's color can be set with setColor().
    void setColor(const QColor& color) { myColor = color; }
    [[nodiscard]] DiagramItem* startItem() const { return myStartItem; }
    [[nodiscard]] DiagramItem* endItem() const { return myEndItem; }
    // Calling updatePosition() causes the arrow to recalculate its position and arrow head angle.
    void updatePosition();

protected:
    // paint() is reimplemented so that we can paint an arrow rather than just a line between items.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    // myStartItem and myEndItem are the diagram items that the arrow connects. The arrow is drawn with its head to the end item.
    DiagramItem* myStartItem;
    DiagramItem* myEndItem;
    // arrowHead is a polygon with three vertices's we use to draw the arrow head.
    QPolygonF arrowHead;
    QColor myColor = Qt::black;
};
