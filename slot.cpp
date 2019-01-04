#include "slot.h"
#include "ui_slot.h"
#include "mainwindow.h"

Slot::Slot(Igrac_slot igrac, int ulog) :
    QDialog(nullptr), m_igrac(igrac), m_ulog(ulog),
    ui(new Ui::Slot)
{
    ui->setupUi(this);
}

Slot::~Slot()
{
    delete ui;
}


void Slot::igraj(){

    while(m_igrac.kredit() >= m_ulog){

        m_poeni = 0;

        m_poeni += provera_matrice();
        if(m_poeni > 0){
            m_igrac.izmeni_kredit(m_poeni);
        }
        else {
            m_igrac.izmeni_kredit(-m_ulog);
        }
        std::cout << "Trenutno imate: " << m_igrac.kredit() << "poena" << std::endl;
    }

    std::cout << "Nemate vise novca" << std::endl;
}

int myrandom (int i) {
    return std::rand()%i;
}

int Slot::provera_matrice(){

    int poeni = 0;
    std::srand(unsigned(std::time(nullptr)));
    random_shuffle(m_vocke.begin(), m_vocke.end(), myrandom);

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

