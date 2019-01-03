#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "igrac_slot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Pocetni prozor");
    this->setFixedSize(500, 500);
    /*
    ui->Slot->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                                  "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");

    ui->Quit->setStyleSheet("QPushButton {background-color: rgb(180, 124, 30); margin: 3px;"
                                  "color: rgb(57, 19, 19); font-weight: bold; font-size: 24px; font-style: italic;}");
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Quit_clicked()
{
    close();
}
