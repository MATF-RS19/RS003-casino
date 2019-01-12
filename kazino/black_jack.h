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
#include "ui_mainwindow.h"


namespace Ui {
class Black_jack;
}

class Black_jack : public QDialog
{
    Q_OBJECT

public:
    explicit Black_jack(Igrac_bj& igrac, int ulog = 100, QMainWindow *MainWindow = nullptr);
    ~Black_jack();

    void igraj();

    void deljenje_karata(QLabel *&labela);
private slots:
    void on_podeli_clicked();

    void on_back_clicked();

    void on_ne_zelim_clicked();

    void on_sledeca_karta_clicked();

    void on_nova_igra_clicked();

    void on_ulog50_clicked();

    void on_ulog100_clicked();

private:
    Igrac_bj* m_igrac;
    Racunar_bj m_racunar;
    int broj_karata_u_spilu = 52;
    std::vector<int> m_karte;
    std::list<int> m_spil;
    int m_pobednik = 0;
    bool odabran_ulog = false;

    QLabel* labela_ulog;
    QLabel* labela_racunar;

    Ui::Black_jack *ui;
    QMainWindow *m_MainWindow;

    QPropertyAnimation *animacija;
    QPropertyAnimation *animacija_za_cipove;


    std::list<QLabel*> m_niz_labela_igrac;
    std::list<QLabel*> m_niz_labela_racunar;

    int m_ulog;

    template<typename T>
    T uzmi_prvi_element(std::list<T>& spil);

    void pocetni_izgled_ekrana();
    QString napravi_putanju(int rb_karte);
    void postavi_kartu(QLabel*& labela, std::string &&ko_igra);
    int izracunaj_zbir();

    void proveri_ulog();
    void provera_pobede();
    void kretanje_cipova(QLabel *&ko_salje, QLabel *&gde_saljem, QPixmap &pix, std::string &&ko_igra);
};

#endif // BLACK_JACK_H
