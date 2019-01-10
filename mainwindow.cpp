#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "igrac_slot.h"
#include "slot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_slot_clicked()
{
    close();
    Igrac_slot igrac("Dusko");
    Slot slot(igrac, 100);

    slot.setModal(true);
    slot.exec();

}

void MainWindow::on_quit_clicked()
{
    close();
}
