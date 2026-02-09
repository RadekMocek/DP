#pragma once

#include <QGraphicsPixmapItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

// DiagramItem inherits QGraphicsPolygonItem and represents a flowchart shape.

/*
The DiagramItem represents a flowchart shape in the DiagramScene. It inherits QGraphicsPolygonItem and has a polygon for each shape.
The enum DiagramType has a value for each of the flowchart shapes. The class has a list of the arrows that are connected to it.
This is necessary because only the item knows when it is being moved (with the itemChanged() function) at which time the arrows must be updated.
The item can also draw itself onto a QPixmap with the image() function. This is used for the tool buttons in MainWindow, see createColorToolButtonIcon() in MainWindow.
The Type enum is a unique identifier of the class. It is used by qgraphicsitem_cast(), which does dynamic casts of graphics items.
The UserType constant is the minimum value a custom graphics item type can be.
*/

class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };

    enum DiagramType { Step, Conditional, StartEnd, Io };

    DiagramItem(DiagramType diagramType, QMenu* contextMenu, QGraphicsItem* parent = nullptr);

    void removeArrow(Arrow* arrow);
    void removeArrows() const;
    DiagramType diagramType() const { return myDiagramType; }
    QPolygonF getMyPolygon() const { return myPolygon; }
    void addArrow(Arrow* arrow);
    QPixmap image() const;
    int type() const override { return Type; }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu* myContextMenu;
    QList<Arrow*> arrows;
};
