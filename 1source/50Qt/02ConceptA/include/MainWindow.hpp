#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPointer>
#include <QSlider>
#include <QTextEdit>
#include <QWidget>

#include "Canvas.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private slots:

private:
    // My state

    // My methods
    void repaint_canvas() const;

    // UI Creation methods
    void create_menus();
    void create_central_widget();

    // UI Widgets
    QPointer<QWidget> central_widget;
    QPointer<QGridLayout> main_layout;
    QPointer<QTextEdit> text_edit;
    QPointer<Canvas> canvas;
    QPointer<QSlider> zoom_level;
};
