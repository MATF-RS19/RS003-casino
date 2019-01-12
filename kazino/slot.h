#ifndef SLOT_H
#define SLOT_H

#include <QDialog>


#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <list>
#include <map>
#include <iterator>
#include <QPropertyAnimation>
#include <QLabel>
#include "igrac_slot.h"


int myrandom (int i);

namespace Ui {
class Slot;
}


class Slot : public QDialog
{
    Q_OBJECT

public:
    explicit Slot(Igrac_slot &igrac, int ulog = 10);
    ~Slot();
    void igraj();

    void kretanje_vockica(QLabel *&labela,unsigned brojac);
private slots:
    void on_pushButton_clicked();

    void on_back_clicked();

    void on_ulog1_clicked();

    void on_ulog2_clicked();

    void on_ulog3_clicked();

    void on_da_clicked();

    void on_ne_clicked();

private:
    Igrac_slot *m_igrac;
    std::vector<int> m_vocke = {1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4,
                                4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 0, 0};
    int m_ulog;
    int m_poeni = 0;
    int m_indikator_za_slot = 1;
    QPropertyAnimation *animacija;

    int provera_matrice();
    void generisi_sliku();
    int provera_pobede(int k1,int k2,int k3);
    Ui::Slot *ui;
    void ukljuci_vidljivost_odluke();
    void iskljuci_vidljivost_odluke();
    void ukljuci_igranje_slota();
    void iskljuci_igranje_slota();
};

#endif // SLOT_H
