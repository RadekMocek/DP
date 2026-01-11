#include <QMessageBox>

#include "MainWindow.hpp"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Qt :: ConceptA");
    resize(1366, 768);

    create_menus();
    create_central_widget();

    repaint_canvas();
}

void MainWindow::repaint_canvas()
{
    canvas->repaint(text_edit->toPlainText());
}


void MainWindow::create_menus()
{
    // Create menu bar
    const QPointer menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    // File menu
    const QPointer help_menu = menu_bar->addMenu("Help");
    const QPointer about_action = help_menu->addAction("About...");
    connect(about_action, &QAction::triggered, [this] {
        QMessageBox::about(this, "About...", "https://github.com/RadekMocek/DP");
    });
}


void MainWindow::create_central_widget()
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    // Create main layout
    main_layout = new QGridLayout();

    // Row 1
    text_edit = new QTextEdit();
    text_edit->setText("10 10 Hello\n120 30 Qt!");

    connect(text_edit, &QTextEdit::textChanged, this, &MainWindow::repaint_canvas);

    main_layout->addWidget(text_edit, 0, 0, 0, 1);

    canvas = new Canvas();
    main_layout->addWidget(canvas, 0, 1);

    // Row 2
    zoom_level = new QSlider(Qt::Horizontal);
    zoom_level->setMinimum(1);
    zoom_level->setMaximum(20);
    zoom_level->setValue(10);

    connect(zoom_level, &QAbstractSlider::valueChanged, [this](const int value) {
        canvas->change_zoom_level(value);
    });

    main_layout->addWidget(zoom_level, 1, 1);

    //
    central_widget->setLayout(main_layout);
}
