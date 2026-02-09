#include "DiagramScene.hpp"
#include "DiagramTextItem.hpp"

// We simply set the item movable and selectable, as these flags are off by default.
DiagramTextItem::DiagramTextItem(QGraphicsItem* parent) : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

// When the item is selected we emit the selectedChanged signal.
// The MainWindow uses this signal to update the widgets that display font properties to the font of the selected text item.
QVariant DiagramTextItem::itemChange(const GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        emit selectedChange(this);
    }
    return value;
}

// DiagramScene uses the signal emitted when the text item loses focus to remove the item if it is empty, i.e., it contains no text.
void DiagramTextItem::focusOutEvent(QFocusEvent* event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

// When we receive a double click event, we make the item editable by calling QGraphicsTextItem::setTextInteractionFlags().
// We then forward the double-click to the item itself.
void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction) {
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
