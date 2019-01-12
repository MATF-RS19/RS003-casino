#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <QMediaPlayer>
#include "igrac.h"
#include "igrac_slot.h"
#include "igrac_bj.h"

bool proveri_broj(bool rezultat, char x);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void prikazi();

private slots:
    void on_slot_clicked();

    void on_quit_clicked();

    void on_prijava_clicked();

    void on_black_jack_clicked();

    void on_mute_clicked();

    void on_unmute_clicked();

private:
    Ui::MainWindow *ui;
    Igrac m_igrac;
    Igrac_slot igrac_slot;
    Igrac_bj igrac_bj;

    QMediaPlayer *muzika;
    bool indikator_za_prijavu = false;
    bool provera_uloga(QString ulog);

};

#endif // MAINWINDOW_H
