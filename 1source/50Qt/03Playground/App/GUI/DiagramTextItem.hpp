#pragma once

#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

// TextDiagramItem inherits QGraphicsTextItem and represents text items in the diagram.
// The class adds support for moving the item with the mouse, which is not supported by QGraphicsTextItem.

/*
The TextDiagramItem class inherits QGraphicsTextItem and adds the possibility to move editable text items.
Editable QGraphicsTextItems are designed to be fixed in place and editing starts when the user single clicks on the item.
With DiagramTextItem the editing starts with a double click leaving single click available to interact with and move it.
*/

class DiagramTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 3 };

    explicit DiagramTextItem(QGraphicsItem* parent = nullptr);

    [[nodiscard]] int type() const override { return Type; }

signals:
    void lostFocus(DiagramTextItem* item);
    void selectedChange(QGraphicsItem* item);

protected:
    // We use itemChange() and focusOutEvent() to notify the DiagramScene when the text item loses focus and gets selected.
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void focusOutEvent(QFocusEvent* event) override;
    // We reimplement the functions that handle mouse events to make it possible to alter the mouse behavior of QGraphicsTextItem.
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};
