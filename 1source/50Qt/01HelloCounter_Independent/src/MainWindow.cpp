#include <QMessageBox>

#include "MainWindow.hpp"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Qt :: Hello Counter");
    resize(800, 600);

    create_menus();
    create_central_widget();

    on_counter_update();
}


void MainWindow::on_counter_update()
{
    label_counter_value->setText(QString::number(counter));

    button_counter_decrement->setEnabled(counter != 1);
    button_counter_increment->setEnabled(counter != 5);

    label_hello->setVisible(counter == 3);
}


void MainWindow::on_button_decrement_clicked()
{
    counter--;
    on_counter_update();
}


void MainWindow::on_button_increment_clicked()
{
    counter++;
    on_counter_update();
}


void MainWindow::on_popup_action_triggered()
{
    QMessageBox::information(this, "Pop-up window", "Not much you can do here...");
}


void MainWindow::create_menus()
{
    // Create menu bar
    QMenuBar* menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    // File menu
    QMenu* file_menu = menu_bar->addMenu("File");
    QAction* popup_action = file_menu->addAction("Pop-up");    
    connect(popup_action, &QAction::triggered, this, &MainWindow::on_popup_action_triggered); // (sender, signal, context, slot)
    QAction* exit_action = file_menu->addAction("Exit");
    connect(exit_action, &QAction::triggered, this, &QWidget::close);
}


void MainWindow::create_central_widget()
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    // Create main layout
    main_layout = new QVBoxLayout(central_widget);

    // Create row of buttons with counter label
    row_counter = new QHBoxLayout();
    main_layout->addLayout(row_counter);

    button_counter_decrement = new QPushButton("-");
    row_counter->addWidget(button_counter_decrement);
    connect(button_counter_decrement, &QPushButton::clicked, this, &MainWindow::on_button_decrement_clicked);

    label_counter_value = new QLabel("?");
    row_counter->addWidget(label_counter_value);

    button_counter_increment = new QPushButton("+");
    row_counter->addWidget(button_counter_increment);
    connect(button_counter_increment, &QPushButton::clicked, this, &MainWindow::on_button_increment_clicked);

    row_counter->addStretch();

    // Second row has only the 'Hello' label
    label_hello = new QLabel("Hello!");
    main_layout->addWidget(label_hello);

    main_layout->addStretch();
}
