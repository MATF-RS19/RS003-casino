#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "slot.h"
#include "black_jack.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pozadina(":/slike/background.jpg");
    pozadina = pozadina.scaled(this->size(), Qt::IgnoreAspectRatio);
    this->setWindowTitle("Pocetni ekran");
    QPalette paleta;
    paleta.setBrush(QPalette::Background, pozadina);
    setPalette(paleta);

    QPixmap zabrana(":/slike/zabrana.png");
    ui->zabrana->setPixmap(zabrana);
    ui->zabrana->setScaledContents(true);

    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);


    ui->slot->setStyleSheet("border-image:url(:/slike/button_slot.png);");
    ui->black_jack->setStyleSheet("border-image:url(:/slike/button_blackjack.png);");
    ui->quit->setStyleSheet("border-image:url(:/slike/button_quit.png);");
    ui->prijava->setStyleSheet("border-image:url(:/slike/button_prijavi_se.png);");

    ui->mute->setStyleSheet("border-image:url(:/slike/mute.png);");
    ui->unmute->setStyleSheet("border-image:url(:/slike/unmute.png);");

    ui->mute->setVisible(true);
    ui->unmute->setVisible(false);

    muzika = new QMediaPlayer();
    muzika->setMedia(QUrl("qrc:/muzika/KAZINO.mp3"));
    muzika->play();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_slot_clicked(){
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    if(indikator_za_prijavu){

        igrac_slot.postavi_ime(m_igrac.ime());
        igrac_slot.postavi_kredit(m_igrac.kredit());

        Slot slot(igrac_slot, 100);
        slot.setModal(true);
        slot.exec();
    }
    else{
        ui->label_5->setVisible(true);
    }
    if(indikator_za_prijavu){
        m_igrac.postavi_kredit(igrac_slot.kredit());
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
        ui->ime_2->setStyleSheet(" font-size:14pt; color:#ffffff;");
        ui->novac->setNum(m_igrac.kredit());
        ui->novac->setStyleSheet(" font-size:14pt; color:#ffffff;");
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

void MainWindow::on_black_jack_clicked(){
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);

    if(indikator_za_prijavu){
        igrac_bj.postavi_ime(m_igrac.ime());
        igrac_bj.postavi_kredit(m_igrac.kredit());

        Black_jack black_jack(igrac_bj, 100);
        black_jack.setModal(true);
        black_jack.exec();
    }
    else{
        ui->label_5->setVisible(true);
    }
    if(indikator_za_prijavu){
        m_igrac.postavi_kredit(igrac_bj.kredit());
        ui->novac->setNum(m_igrac.kredit());
    }
}

void MainWindow::on_mute_clicked(){
    muzika->stop();
    ui->mute->setVisible(false);
    ui->unmute->setVisible(true);
}



void MainWindow::on_unmute_clicked(){
    muzika->play();
    ui->mute->setVisible(true);
    ui->unmute->setVisible(false);
}
