#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include <QDialog>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <list>
#include <random>
#include <chrono>
#include <QLabel>
#include <QPropertyAnimation>

#include "igrac_bj.h"
#include "racunar_bj.h"



namespace Ui {
class Black_jack;
}

class Black_jack : public QDialog
{
    Q_OBJECT

public:
    explicit Black_jack(Igrac_bj& igrac, int ulog = 100);
    ~Black_jack();

    void igraj();

    void deljenje_karata(QLabel *&labela);
private slots:
    void on_podeli_clicked();

    void on_back_clicked();

    void on_ne_zelim_clicked();

    void on_sledeca_karta_clicked();

    void on_nova_igra_clicked();

private:
    Igrac_bj* m_igrac;
    Racunar_bj m_racunar;
    int broj_karata_u_spilu = 52;
    std::vector<int> m_karte;
    std::list<int> m_spil;


    QPropertyAnimation *animacija;

    std::list<QLabel*> m_niz_labela_igrac;
    std::list<QLabel*> m_niz_labela_racunar;

    int m_ulog;

    template<typename T>
    T uzmi_prvi_element(std::list<T>& spil);

    void pocetni_izgled_ekrana();
    QString napravi_putanju(int rb_karte);
    void postavi_kartu(QLabel*& labela, std::string &&ko_igra);
    int izracunaj_zbir();
    Ui::Black_jack *ui;
};

#endif // BLACK_JACK_H
