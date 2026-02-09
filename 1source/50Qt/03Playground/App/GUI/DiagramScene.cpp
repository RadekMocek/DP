#include "Arrow.hpp"
#include "DiagramScene.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>

// The scene uses myItemMenu to set the context menu when it creates DiagramItems.
// We set the default mode to DiagramScene::MoveItem as this gives the default behavior of QGraphicsScene.
DiagramScene::DiagramScene(QMenu* itemMenu, QObject* parent) : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = DiagramItem::Step;
    line = nullptr;
    textItem = nullptr;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
}

// The isItemChange function returns true if an Arrow item is selected in the scene in which case we want to change its color.
// When the DiagramScene creates and adds new arrows to the scene it will also use the new color.
void DiagramScene::setLineColor(const QColor& color)
{
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {
        const auto item = qgraphicsitem_cast<Arrow*>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}

// This function sets the color of DiagramTextItems equal to the way setLineColor() sets the color of Arrows.
void DiagramScene::setTextColor(const QColor& color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {
        auto* item = qgraphicsitem_cast<DiagramTextItem*>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}

// This function sets the color the scene will use when creating DiagramItems. It also changes the color of a selected DiagramItem.
void DiagramScene::setItemColor(const QColor& color)
{
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {
        auto* item = qgraphicsitem_cast<DiagramItem*>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}

// Set the font to use for new and selected, if a text item is selected, DiagramTextItems.
void DiagramScene::setFont(const QFont& font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (QGraphicsTextItem* item = qgraphicsitem_cast<DiagramTextItem*>(selectedItems().first())) {
            item->setFont(myFont);
        }
    }
}

void DiagramScene::setMode(const Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(const DiagramItem::DiagramType type)
{
    myItemType = type;
}

// DiagramTextItems emit a signal when they lose focus, which is connected to this slot.
// We remove the item if it has no text. If not, we would leak memory and confuse the user as the items will be edited when pressed on by the mouse.
void DiagramScene::editorLostFocus(DiagramTextItem* item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}

// The mousePressEvent() function handles mouse press event's different depending on which mode the DiagramScene is in. We examine its implementation for each mode.
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    DiagramItem* item;
    switch (myMode) {
    case InsertItem:
        // We simply create a new DiagramItem and add it to the scene at the position the mouse was pressed.
        // Note that the origin of its local coordinate system will be under the mouse pointer position.
        item = new DiagramItem(myItemType, myItemMenu);
        item->setBrush(myItemColor);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit itemInserted(item);
        break;
    case InsertLine:
        // The user adds Arrows to the scene by stretching a line between the items the arrow should connect.
        // The start of the line is fixed in the place the user clicked the mouse and the end follows the mouse pointer as long as the button is held down.
        // When the user releases the mouse button an Arrow will be added to the scene if there is a DiagramItem under the start and end of the line.
        // We will see how this is implemented later; here we simply add the line.
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        line->setPen(QPen(myLineColor, 2));
        addItem(line);
        break;
    case InsertText:
        // The DiagramTextItem is editable when the Qt::TextEditorInteraction flag is set, else it is movable by the mouse.
        // We always want the text to be drawn on top of the other items in the scene, so we set the value to a number higher than other items in the scene.
        textItem = new DiagramTextItem();
        textItem->setFont(myFont);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setZValue(1000.0);
        connect(textItem, &DiagramTextItem::lostFocus, this, &DiagramScene::editorLostFocus);
        connect(textItem, &DiagramTextItem::selectedChange, this, &DiagramScene::itemSelected);
        addItem(textItem);
        textItem->setDefaultTextColor(myTextColor);
        textItem->setPos(mouseEvent->scenePos());
        emit textInserted(textItem);
    default:
        // We are in MoveItem mode if we get to the default switch; we can then call the QGraphicsScene implementation, which handles movement of items with the mouse.
        // We make this call even if we are in another mode making it possible to add an item and then keep the mouse button pressed down and start moving the item.
        // In the case of text items, this is not possible as they do not propagate mouse events when they are editable.
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // We must draw the line if we are in InsertMode and the mouse button is pressed down (the line is not 0).
    // As discussed in mousePressEvent() the line is drawn from the position the mouse was pressed to the current position of the mouse.
    if (myMode == InsertLine && line != nullptr) {
        const QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }
    // If we are in MoveItem mode, we call the QGraphicsScene implementation, which handles movement of items.
    else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // First we need to get the items (if any) under the line's start and end points.
    // The line itself is the first item at these points, so we remove it from the lists. As a precaution, we check if the lists are empty, but this should never happen.
    if (line != nullptr && myMode == InsertLine) {
        QList<QGraphicsItem*> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line) {
            startItems.removeFirst();
        }

        QList<QGraphicsItem*> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line) {
            endItems.removeFirst();
        }

        removeItem(line);
        delete line;

        // Now we check if there are two different DiagramItems under the lines start and end points. If there are we can create an Arrow with the two items.
        // The arrow is then added to each item and finally the scene. The arrow must be updated to adjust its start and end points to the items.
        // We set the z-value of the arrow to -1000.0 because we always want it to be drawn under the items.

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == DiagramItem::Type &&
            endItems.first()->type() == DiagramItem::Type &&
            startItems.first() != endItems.first()) {
            const auto startItem = qgraphicsitem_cast<DiagramItem*>(startItems.first());
            auto* endItem = qgraphicsitem_cast<DiagramItem*>(endItems.first());
            auto* arrow = new Arrow(startItem, endItem);
            arrow->setColor(myLineColor);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
    }
    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

// The scene has single selection, i.e., only one item can be selected at any given time.
// The for loop will then loop one time with the selected item or none if no item is selected.
// isItemChange() is used to check whether a selected item exists and also is of the specified diagram type.
bool DiagramScene::isItemChange(int type) const
{
    const QList<QGraphicsItem*> items = selectedItems();
    const auto cb = [type](const QGraphicsItem* item) { return item->type() == type; };
    return std::ranges::find_if(items, cb) != items.end();
}
