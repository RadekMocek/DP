#include <QtWidgets/QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_counter_update();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_counter_update()
{
    ui->label_counter->setText(QString::number(counter));

    ui->button_minus->setEnabled(counter != 1);
    ui->button_plus->setEnabled(counter != 5);

    ui->label_hello->setVisible(counter == 3);
}


void MainWindow::on_button_minus_clicked()
{
    counter--;
    on_counter_update();
}


void MainWindow::on_button_plus_clicked()
{
    counter++;
    on_counter_update();
}


void MainWindow::on_actionPop_up_triggered()
{
    QMessageBox::information(this, "Pop-up window", "Not much you can do here...");
}


void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::exit();
}

