#include "manja_veca.h"
#include "ui_manja_veca.h"
#include "slot.h"

Manja_veca::Manja_veca(Igrac_slot& igrac, int poeni, int ulog) :
    QDialog(nullptr),
    ui(new Ui::Manja_veca), m_igrac(&igrac), m_poeni(poeni), m_ulog(ulog)
{
    ui->setupUi(this);
    generisi_pocetnu_sliku();
}

void Manja_veca::generisi_pocetnu_sliku(){
    ui->nastavljam->setVisible(false);
    ui->Izadji->setVisible(false);
    QPixmap pix(":/slike/karta.png");
    ui->sakrivena->setPixmap(pix);
    ui->sakrivena->setScaledContents(true);

    ui->zarada->setNum(m_poeni);

    ui->manja->setVisible(true);
    ui->veca->setVisible(true);


    std::srand(unsigned (std::time(nullptr)));

    random_shuffle(m_karte.begin(), m_karte.end(), myrandom);
    std::list<int> spil(m_karte.size());
    std::copy(m_karte.begin(), m_karte.end(), spil.begin());
    m_igrac->dodaj_kartu(uzmi_kartu(spil));

    QPixmap pix1(nadji_putanju(m_igrac->karta()));

    ui->igrac->setPixmap(pix1);
    ui->igrac->setScaledContents(true);

    m_skrivena_karta = uzmi_kartu(spil);

}

Manja_veca::~Manja_veca()
{
    delete ui;
}

QString Manja_veca::nadji_putanju(int karta){
    QString folder = ":/slike/tref";
    std::string broj = std::to_string(karta);
    QString str_karta = QString::fromUtf8(broj.c_str());
    QString ime_fajla = folder.append(str_karta).append(".png");

    return  ime_fajla;
}

void Manja_veca::igraj(){

    QPixmap pix(nadji_putanju(m_skrivena_karta));
    ui->sakrivena->setPixmap(pix);
    ui->sakrivena->setScaledContents(true);
    ui->manja->setVisible(false);
    ui->veca->setVisible(false);

    if(m_indikator == 1){
        if(m_igrac->karta() < m_skrivena_karta){
            m_poeni = 2*m_poeni;
            ui->nastavljam->setVisible(true);
        }
        else{
            m_poeni = -m_ulog;
            ui->odustajem->setVisible(false);
            ui->Izadji->setVisible(true);
        }
    }
    else if(m_indikator == 2){
        if(m_igrac->karta() > m_skrivena_karta){
            m_poeni = 2*m_poeni;
            ui->nastavljam->setVisible(true);
        }
        else{
            m_poeni = -m_ulog;
            ui->odustajem->setVisible(false);
            ui->Izadji->setVisible(true);
        }
    }
}

int Manja_veca::uzmi_kartu(std::list<int>& spil){
    auto it = spil.begin();
    std::advance(it, 0);

    spil.pop_front();

    return *it;
}

void Manja_veca::on_manja_clicked(){
    m_indikator = 1;
    igraj();

}

void Manja_veca::on_veca_clicked(){
    m_indikator = 2;
    igraj();
}

void Manja_veca::on_nastavljam_clicked(){
    generisi_pocetnu_sliku();
}

void Manja_veca::on_odustajem_clicked(){
    m_igrac->izmeni_kredit(m_poeni);
    close();
}

void Manja_veca::on_Izadji_clicked(){
    m_igrac->izmeni_kredit(-m_ulog);
    close();
}
