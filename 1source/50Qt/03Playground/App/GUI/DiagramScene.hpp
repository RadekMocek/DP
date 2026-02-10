#pragma once

#include "DiagramItem.hpp"
#include "DiagramTextItem.hpp"

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

// DiagramScene inherits QGraphicsScene
// and provides support for DiagramItem, Arrow and DiagramTextItem (In addition to the support already handled by QGraphicsScene).

/*
In the DiagramScene a mouse click can give three different actions: the item under the mouse can be moved, an item may be inserted,
or an arrow may be connected between to diagram items. Which action a mouse click has depends on the mode, given by the Mode enum, the scene is in.
The mode is set with the setMode() function. The scene also sets the color of its items and the font of its text items.
The colors and font used by the scene can be set with the setLineColor(), setTextColor(), setItemColor() and setFont() functions.
The type of DiagramItem, given by the DiagramItem::DiagramType function, to be created when an item is inserted is set with the setItemType() slot.
The MainWindow and DiagramScene share responsibility for the examples functionality.
MainWindow handles the following tasks: the deletion of items, text, and arrows; moving diagram items to the back and front; and setting the scale of the scene.
*/

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    explicit DiagramScene(QMenu* itemMenu, QObject* parent = nullptr);
    //QFont font() const { return myFont; }
    [[nodiscard]] QColor textColor() const { return myTextColor; }
    [[nodiscard]] QColor itemColor() const { return myItemColor; }
    [[nodiscard]] QColor lineColor() const { return myLineColor; }
    void setLineColor(const QColor& color);
    void setTextColor(const QColor& color);
    void setItemColor(const QColor& color);
    // ReSharper disable once CppHidingFunction
    void setFont(const QFont& font);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);
    void editorLostFocus(DiagramTextItem* item);

signals:
    void itemInserted(DiagramItem* item);
    void textInserted(QGraphicsTextItem* item);
    void itemSelected(QGraphicsItem* item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
    [[nodiscard]] bool isItemChange(int type) const;

    DiagramItem::DiagramType myItemType;
    QMenu* myItemMenu;
    Mode myMode;
    bool leftButtonDown{};
    QPointF startPoint;
    QGraphicsLineItem* line;
    QFont myFont;
    DiagramTextItem* textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
};
