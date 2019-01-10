#include "slot.h"
#include "ui_slot.h"
#include "mainwindow.h"
#include "odluka.h"

Slot::Slot(Igrac_slot igrac, int ulog) :
    QDialog(nullptr), m_igrac(igrac), m_ulog(ulog),
    ui(new Ui::Slot)
{
    ui->setupUi(this);
    generisi_sliku();
    ui->poeni->setNum(m_poeni);
    ui->kredit->setNum(m_igrac.kredit());

}

Slot::~Slot()
{
    delete ui;
}


void Slot::igraj(){

    if(m_igrac.kredit() >= m_ulog){

        m_poeni = 0;

        m_poeni += provera_matrice();
        ui->poeni->setNum(m_poeni);
        if(m_poeni > 0){
            Odluka odluka(m_igrac, m_poeni, m_ulog);
            odluka.setModal(true);
            odluka.exec();
        }
        else {
            m_igrac.izmeni_kredit(-m_ulog);
        }
        ui->kredit->setNum(m_igrac.kredit());

    }
    else {
        ui->poruka->setText("NEMATE VISE KREDITA");
    }
}

int myrandom (int i) {
    return std::rand()%i;
}

int Slot::provera_matrice(){

    int poeni = 0;
    generisi_sliku();

    std::vector<int> kolona1(3);
    std::copy(m_vocke.begin(), m_vocke.begin()+3, kolona1.begin());

    std::vector<int> kolona2(3);
    std::copy(m_vocke.begin()+3, m_vocke.begin()+6, kolona2.begin());

    std::vector<int> kolona3(3);
    std::copy(m_vocke.begin()+6, m_vocke.begin()+9, kolona3.begin());

    poeni += provera_pobede(kolona1.at(0),kolona2.at(1),kolona3.at(2));
    poeni += provera_pobede(kolona1.at(2),kolona2.at(1),kolona3.at(0));

    unsigned i=0;
    while(i < 3){
        poeni += provera_pobede(kolona1.at(i),kolona2.at(i),kolona3.at(i));
        i++;
    }

    return poeni;
}

int Slot::provera_pobede(int k1, int k2, int k3){
    if(k1 == k2 and k2 == k3 and k1 != 0){
        std::cout << m_ulog << std::endl;
        return k1*m_ulog;
    }
    else if((k1 == k2 && k3 == 0) || (k1 == k3 && k2 == 0) || (k3 == k2 && k1 == 0))
        return 6*m_ulog;
    else if((k1 == k2 and k1 == 0) || (k1 == k3 and k1 == 0) || (k3 == k2 and k2 == 0))
        return 8*m_ulog;
    else if(k1 == k2 and k2 == k3 and k1 == 0)
        return 10*m_ulog;
    else
        return 0;
}

void Slot::generisi_sliku(){

    std::srand(unsigned(std::time(nullptr)));
    random_shuffle(m_vocke.begin(), m_vocke.end(), myrandom);
    std::vector<QLabel*> niz_labela = {ui->slika_1, ui->slika_2, ui->slika_3, ui->slika_4, ui->slika_5,
                                       ui->slika_6, ui->slika_7, ui->slika_8, ui->slika_9};

    for(unsigned i = 0; i<9; i++){
        QString folder = ":/slike/";
        std::string broj = std::to_string(m_vocke.at(i));
        QString vocka = QString::fromUtf8(broj.c_str());
        QString ime_fajla = folder.append(vocka).append(".png");
        QPixmap pix(ime_fajla);
        niz_labela.at(i)->setPixmap(pix);
        niz_labela.at(i)->setScaledContents(true);
    }

}

void Slot::on_pushButton_clicked()
{
    igraj();
}

