#include "slot.h"
#include "ui_slot.h"
#include "mainwindow.h"
#include "manja_veca.h"



Slot::Slot(Igrac_slot &igrac, int ulog, QMainWindow *MainWindow) :
    QDialog(nullptr), m_igrac(&igrac), m_ulog(ulog),
    ui(new Ui::Slot), m_MainWindow(MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SLOT");

    ui->back->setStyleSheet("border-image:url(:/slike/back.png);");
    ui->pushButton->setStyleSheet("border-image:url(:/slike/push_button.png);");
    ui->da->setStyleSheet("border-image:url(:/slike/DA.png);");
    ui->ne->setStyleSheet("border-image:url(:/slike/NE.png);");
    ui->ulog1->setStyleSheet("border-image:url(:/slike/50.png);");
    ui->ulog2->setStyleSheet("border-image:url(:/slike/100.png);");
    ui->ulog3->setStyleSheet("border-image:url(:/slike/200.png);");
    ui->kredit->setStyleSheet("font-size:14pt; font-weight:600; color:#ffffff;");
    ui->poeni->setStyleSheet("font-size:14pt; font-weight:600; color:#ffffff;");
    ui->poruka->setStyleSheet("font-size:14pt; font-weight:600; color:#ffffff;");


    QPixmap pozadina(":/slike/slot_backg.jpg");
    pozadina = pozadina.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette paleta;
    paleta.setBrush(QPalette::Background, pozadina);
    setPalette(paleta);

    generisi_sliku();

}

Slot::~Slot()
{
    delete ui;
}

void Slot::ukljuci_vidljivost_odluke(){
    ui->da->setVisible(true);
    ui->ne->setVisible(true);
    ui->pitanje->setVisible(true);
    ui->OsvojiliSte->setVisible(true);
    ui->poeni->setVisible(true);
}
void Slot::iskljuci_vidljivost_odluke(){

    ui->da->setVisible(false);
    ui->ne->setVisible(false);
    ui->pitanje->setVisible(false);
    ui->OsvojiliSte->setVisible(false);
    ui->poeni->setVisible(false);

}

void Slot::igraj(){

    if(m_igrac->kredit() >= m_ulog){

        m_poeni = 0;

        m_poeni += provera_matrice();
        if(m_poeni > 0){
            ukljuci_vidljivost_odluke();
            ui->poeni->setNum(m_poeni);

            iskljuci_igranje_slota();

        }
        else {
            m_igrac->izmeni_kredit(-m_ulog);
        }
        ui->kredit->setNum(m_igrac->kredit());

    }
    else {
        ui->poruka->setText("NEMATE VISE KREDITA");
    }
}

void Slot::kretanje_vockica(QLabel*& labela,unsigned brojac){


    animacija = new QPropertyAnimation(labela, "geometry");


    QLabel* pocetna;
    if(brojac<3)
        pocetna=ui->start_1;
    else if(brojac>2 && brojac<6)
        pocetna=ui->start_2;
    else
        pocetna=ui->start_3;

    animacija->setDuration(200);
    animacija->setStartValue(pocetna->geometry());
    animacija->setEndValue(labela->geometry());
    animacija->start();


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

    iskljuci_vidljivost_odluke();

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
        kretanje_vockica(niz_labela.at(i),i);
    }
    ui->kredit->setNum(m_igrac->kredit());


}

void Slot::on_pushButton_clicked()
{
    igraj();
}



void Slot::on_back_clicked(){
    m_MainWindow->show();
    close();
}

void Slot::on_ulog1_clicked()
{
    m_ulog = 50;
}

void Slot::on_ulog2_clicked(){
    m_ulog = 100;
}

void Slot::on_ulog3_clicked(){
    m_ulog = 200;
}

void Slot::ukljuci_igranje_slota(){
    ui->ulog1->setVisible(true);
    ui->ulog2->setVisible(true);
    ui->ulog3->setVisible(true);
    ui->pushButton->setVisible(true);
}

void Slot::iskljuci_igranje_slota(){
    ui->ulog1->setVisible(false);
    ui->ulog2->setVisible(false);
    ui->ulog3->setVisible(false);
    ui->pushButton->setVisible(false);

}

void Slot::on_da_clicked(){

    ukljuci_igranje_slota();
    iskljuci_vidljivost_odluke();

    Manja_veca manja_veca(*m_igrac, m_poeni, m_ulog);
    manja_veca.setModal(true);
    manja_veca.exec();
    ui->kredit->setNum(m_igrac->kredit());


}

void Slot::on_ne_clicked(){

    ukljuci_igranje_slota();
    iskljuci_vidljivost_odluke();

    m_igrac->izmeni_kredit(m_poeni);
    ui->kredit->setNum(m_igrac->kredit());

}
