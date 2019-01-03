#include "mainwindow.h"
#include <QApplication>

#include "igrac.h"
#include "igrac_slot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
