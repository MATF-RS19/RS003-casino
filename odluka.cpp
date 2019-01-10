#include "odluka.h"
#include "ui_odluka.h"
#include "manja_veca.h"

Odluka::Odluka(Igrac_slot& igrac, int poeni, int ulog) :
    QDialog(nullptr), m_igrac(&igrac),  m_poeni(poeni), m_ulog(ulog),
    ui(new Ui::Odluka)
{
    ui->setupUi(this);
    ui->poeni->setNum(m_poeni);
}

Odluka::~Odluka()
{
    delete ui;
}

void Odluka::on_pushButton_2_clicked(){
    m_igrac->izmeni_kredit(m_poeni);
    close();
}

void Odluka::on_pushButton_clicked(){

    Manja_veca manja_veca(*m_igrac, m_poeni, m_ulog);
    manja_veca.setModal(true);
    manja_veca.exec();
    close();
}
