#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private slots:
    void on_button_decrement_clicked();
    void on_button_increment_clicked();
    void on_popup_action_triggered();

private:
    // My state
    int counter = 1;

    // My functions
    void on_counter_update();    

    // UI Creation methods
    void create_menus();
    void create_central_widget();

    // UI Widgets
    QWidget* central_widget;
    QVBoxLayout* main_layout;
    
    QHBoxLayout* row_counter;

    QPushButton* button_counter_decrement;
    QPushButton* button_counter_increment;
    QLabel* label_counter_value;
    QLabel* label_hello;
};