#include "Arrow.hpp"
#include "DiagramItem.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

// In the constructor we create the items polygon according to diagramType. QGraphicsItems are not movable or selectable by default, so we must set these properties.
DiagramItem::DiagramItem(const DiagramType diagramType, QMenu* contextMenu, QGraphicsItem* parent) :
    QGraphicsPolygonItem(parent), myDiagramType(diagramType), myContextMenu(contextMenu)
{
    QPainterPath path;
    switch (myDiagramType) {
    case StartEnd:
        path.moveTo(200, 50);
        path.arcTo(150, 0, 50, 50, 0, 90);
        path.arcTo(50, 0, 50, 50, 90, 90);
        path.arcTo(50, 50, 50, 50, 180, 90);
        path.arcTo(150, 50, 50, 50, 270, 90);
        path.lineTo(200, 25);
        myPolygon = path.toFillPolygon();
        break;
    case Conditional:
        myPolygon <<
            QPointF(-100, 0) << QPointF(0, 100) << QPointF(100, 0) << QPointF(0, -100) << QPointF(-100, 0);
        break;
    case Step:
        myPolygon <<
            QPointF(-100, -100) << QPointF(100, -100) << QPointF(100, 100) << QPointF(-100, 100) << QPointF(-100, -100);
        break;
    default:
        myPolygon <<
            QPointF(-120, -80) << QPointF(-70, 80) << QPointF(120, 80) << QPointF(70, -80) << QPointF(-120, -80);
        break;
    }
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

// removeArrow() is used to remove Arrow items when they or DiagramItems they are connected to are removed from the scene.
void DiagramItem::removeArrow(Arrow* arrow)
{
    arrows.removeAll(arrow);
}

// This function is called when the item is removed from the scene and removes all arrows that are connected to this item.
// The arrow must be removed from the arrows list of both its start and end item.
// Since either the start or the end item is the object where this function is currently called,
// we have to make sure to work on a copy of arrows since removeArrow() is modifying this container.
void DiagramItem::removeArrows() const
{
    // need a copy here since removeArrow() will modify the arrows container
    for (const auto arrowsCopy = arrows; Arrow* arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

// This function simply adds the arrow to the items arrows list.
void DiagramItem::addArrow(Arrow* arrow)
{
    arrows.append(arrow);
}

// This function draws the polygon of the item onto a QPixmap. In this example we use this to create icons for the tool buttons in the tool box.
QPixmap DiagramItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}

// We show the context menu. As right mouse clicks, which shows the menu, don't select items by default we set the item selected with setSelected().
// This is necessary since an item must be selected to change its elevation with the bringToFront and sendToBack actions.
void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->popup(event->screenPos());
}

// If the item has moved, we need to update the positions of the arrows connected to it. The implementation of QGraphicsItem does nothing, so we just return value.
QVariant DiagramItem::itemChange(const GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow* arrow : std::as_const(arrows)) {
            arrow->updatePosition();
        }
    }

    return value;
}
