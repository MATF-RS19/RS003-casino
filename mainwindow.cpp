#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "slot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pozadina(":/slike/background.jpg");
    pozadina = pozadina.scaled(this->size(), Qt::IgnoreAspectRatio);

    QPalette paleta;
    paleta.setBrush(QPalette::Background, pozadina);
    setPalette(paleta);

    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

    ui->slot->setStyleSheet("border-image:url(:/slike/button_slot.png);");
    ui->black_jack->setStyleSheet("border-image:url(:/slike/button_blackjack.png);");
    ui->quit->setStyleSheet("border-image:url(:/slike/button_quit.png);");
    ui->prijava->setStyleSheet("border-image:url(:/slike/button_prijavi_se.png);");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_slot_clicked()
{
    if(indikator_za_prijavu){
        Igrac_slot igrac(m_igrac.ime(), m_igrac.kredit());

        kopija = igrac;
        Slot slot(kopija, 100);


        slot.setModal(true);
        slot.exec();
    }
    else{
        ui->label_5->setVisible(true);
    }
    if(indikator_za_prijavu){
        m_igrac.postavi_kredit(kopija.kredit());
        ui->novac->setNum(m_igrac.kredit());
    }


}

void MainWindow::on_quit_clicked()
{
    close();
}

void MainWindow::on_prijava_clicked(){
    QString qime = ui->ime->text();
    std::string ime = qime.toUtf8().constData();

    QString qulog = ui->ulog->text();
    int ulog = qulog.toInt();

    bool provera = provera_uloga(qulog);

    if(ui->ulog->text()!= "" and ui->ime->text() != "" and provera){
        indikator_za_prijavu = true;
        m_igrac.postavi_ime(ime);
        m_igrac.postavi_kredit(ulog);
        ui->ime->clear();
        ui->ulog->clear();


        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->ime_2->setText(qime);
        ui->novac->setNum(m_igrac.kredit());
    }
    else{
        ui->label_6->setVisible(true);
    }
}

bool proveri_broj(bool rezultat, char x){
    if(std::isdigit(x))
        return  rezultat && 1;
    else {
        return rezultat && 0;
    }
}

bool MainWindow::provera_uloga(QString qulog){
    std::string ulog = qulog.toUtf8().data();
    bool provera = std::accumulate(ulog.begin(), ulog.end(), true, proveri_broj);

    return provera;

}

