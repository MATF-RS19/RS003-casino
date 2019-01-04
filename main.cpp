#include "mainwindow.h"
#include <QApplication>

#include "igrac.h"
#include "igrac_slot.h"
#include "slot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Igrac_slot igrac("Dusko", 1000);
    Slot slot(igrac, 100);
    slot.igraj();

    return a.exec();
}
