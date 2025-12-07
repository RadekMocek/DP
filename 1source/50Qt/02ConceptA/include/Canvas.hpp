#pragma once

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget* parent = nullptr);
    void repaint(const QString& str);
    void change_zoom_level(int new_zoom_level);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    struct node
    {
        int x;
        int y;
        QString text;
    };

    QPoint origin;

    QList<node> nodes;

    QFont font;
    QFontMetrics font_metrics;

    bool is_moving_canvas = false;
    QPoint moving_canvas_start_cursor_pos{};
    QPoint moving_canvas_start_origin{};

    float zoom_level = 1.0f;

    static constexpr int node_padding_horizontal = 5;
};
