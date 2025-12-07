#include <QMouseEvent>
#include <QPainter>

#include "Canvas.hpp"


Canvas::Canvas(QWidget* parent) :
    QWidget(parent),
    origin({0, 0}),
    font(QFont("Courier", 22)),
    font_metrics(QFontMetrics(font)) {}


void Canvas::repaint(const QString& str)
{
    nodes.clear();

    auto lines = str.split("\n");

    for (const auto& line : lines) {
        if (auto parts = line.split(" "); parts.length() >= 3) {
            nodes.append(node{
                parts[0].toInt(),
                parts[1].toInt(),
                parts[2]
            });
        }
    }

    this->update();
}


void Canvas::change_zoom_level(const int new_zoom_level)
{
    zoom_level = new_zoom_level / 10.0f;

    font.setPointSizeF(22 * zoom_level);
    font_metrics = QFontMetrics(font);

    this->update();
}


void Canvas::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setFont(font);

    const auto padding = node_padding_horizontal * zoom_level;

    for (const auto& [_x, _y, text] : nodes) {
        const auto rect = font_metrics.boundingRect(text);
        const auto width = rect.width();
        const auto height = rect.height();

        const auto x = (_x + origin.x()) * zoom_level;
        const auto y = (_y + origin.y()) * zoom_level;

        painter.drawRect(x - padding, y, width + 2 * padding, height);
        painter.drawText(QPoint(x, y + static_cast<int>(height * .75)), text);
    }
}


void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        is_moving_canvas = true;
        moving_canvas_start_cursor_pos = event->pos();
        moving_canvas_start_origin = origin;
    }
}


void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if (is_moving_canvas) {
        origin = moving_canvas_start_origin + (event->pos() - moving_canvas_start_cursor_pos) / zoom_level;
        this->update();
    }
}


void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton && is_moving_canvas) {
        is_moving_canvas = false;
    }
}
