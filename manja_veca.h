#ifndef MANJA_VECA_H
#define MANJA_VECA_H

#include <QDialog>
#include "igrac_slot.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <list>
#include<random>
#include<chrono>


namespace Ui {
class Manja_veca;
}

class Manja_veca : public QDialog
{
    Q_OBJECT

public:
    explicit Manja_veca(Igrac_slot& igrac, int poeni, int ulog);
    ~Manja_veca();

    int uzmi_kartu(std::list<int>& spil);
    void igraj();

private slots:
    void on_manja_clicked();

    void on_veca_clicked();

    void on_nastavljam_clicked();

    void on_odustajem_clicked();

private:
    Ui::Manja_veca *ui;
    Igrac_slot *m_igrac;
    int m_poeni;
    int m_ulog;
    std::vector<int> m_karte = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int m_indikator;
    int m_skrivena_karta;

    QString nadji_putanju(int karta);


};

#endif // MANJA_VECA_H
