#include "Arrow.hpp"
#include "DiagramItem.hpp"

#include <QPainter>
#include <QPen>
#include <QtMath>

// We set the start and end diagram items of the arrow. The arrow head will be drawn where the line intersects the end item.
Arrow::Arrow(DiagramItem* startItem, DiagramItem* endItem, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

// We need to reimplement this function because the arrow is larger than the bounding rectangle of the QGraphicsLineItem.
// The graphics scene uses the bounding rectangle to know which regions of the scene to update.
QRectF Arrow::boundingRect() const
{
    const qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y()))
           .normalized().adjusted(-extra, -extra, extra, extra);
}

// The shape function returns a QPainterPath that is the exact shape of the item.
// The QGraphicsLineItem::shape() returns a path with a line drawn with the current pen, so we only need to add the arrow head.
// This function is used to check for collisions and selections with the mouse.
QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

// This slot updates the arrow by setting the start and end points of its line to the center of the items it connects.
void Arrow::updatePosition()
{
    const QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void Arrow::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // If the start and end items collide we do not draw the arrow; the algorithm we use to find the point the arrow should be drawn at may fail if the items collide.
    if (myStartItem->collidesWithItem(myEndItem)) {
        return;
    }

    // We first set the pen and brush we will use for drawing the arrow.
    QPen myPen = pen();
    myPen.setColor(myColor);
    constexpr qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    // We then need to find the position at which to draw the arrowhead. The head should be drawn where the line and the end item intersects.
    // This is done by taking the line between each point in the polygon and check if it intersects with the line of the arrow.
    // Since the line start and end points are set to the center of the items the arrow line should intersect one and only one of the lines of the polygon.
    // Note that the points in the polygon are relative to the local coordinate system of the item.
    // We must therefore add the position of the end item to make the coordinates relative to the scene.
    const QLineF centerLine(myStartItem->pos(), myEndItem->pos());
    QPolygonF endPolygon = myEndItem->getMyPolygon();
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF intersectPoint;
    for (int i = 1; i < endPolygon.count(); ++i) {
        QPointF p2 = endPolygon.at(i) + myEndItem->pos();
        auto polyLine = QLineF(p1, p2);
        if (const QLineF::IntersectionType intersectionType = polyLine.intersects(centerLine, &intersectPoint);
            intersectionType == QLineF::BoundedIntersection) {
            break;
        }
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, myStartItem->pos()));

    // We calculate the angle between the x-axis and the line of the arrow. We need to turn the arrow head to this angle so that it follows the direction of the arrow.
    // If the angle is negative we must turn the direction of the arrow.
    const double angle = std::atan2(-line().dy(), line().dx());

    // We can then calculate the three points of the arrow head polygon.
    // One of the points is the end of the line, which now is the intersection between the arrow line and the end polygon.
    // Then we clear the arrowHead polygon from the previous calculated arrow head and set these new points.
    const QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI / 3) * arrowSize);
    const QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    // If the line is selected, we draw two dotted lines that are parallel with the line of the arrow.
    // We do not use the default implementation, which uses boundingRect() because the QRect bounding rectangle is considerably larger than the line.
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0, -8.0);
        painter->drawLine(myLine);
    }
}
