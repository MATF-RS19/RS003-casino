#include "black_jack.h"
#include "ui_black_jack.h"
#include "slot.h"

Black_jack::Black_jack(Igrac_bj &igrac, int ulog, QMainWindow *MainWindow) :
    QDialog(nullptr), m_igrac(&igrac),
    ui(new Ui::Black_jack), m_MainWindow(MainWindow), m_ulog(ulog)
{
    ui->setupUi(this);

    ui->ulog50->setStyleSheet("border-image:url(:/slike/cip50.png);");
    ui->ulog100->setStyleSheet("border-image:url(:/slike/cip100.png);");
    ui->novac->setStyleSheet(" font-size:14pt; color:#ffffff;");
    ui->rezultat->setStyleSheet(" font-size:14pt; color:#ffffff;");
    ui->back->setStyleSheet("border-image:url(:/slike/back_bj.png);");
    ui->ne_zelim->setStyleSheet("border-image:url(:/slike/button_ne-zelim-da-vucem.png);");
    ui->sledeca_karta->setStyleSheet("border-image:url(:/slike/button_sledeca-karta.png);");
    ui->nova_igra->setStyleSheet("border-image:url(:/slike/button_nova-igra.png);");
    this->setWindowTitle("Blackjack");

    for(int i = 0; i<broj_karata_u_spilu; i++){
        m_karte.push_back(i);
    }

    QPixmap pozadina(":/slike/blackjack_sto.jpg");
    pozadina = pozadina.scaled(this->size(), Qt::IgnoreAspectRatio);

    QPalette paleta;
    paleta.setBrush(QPalette::Background, pozadina);
    setPalette(paleta);

    ui->podeli->setStyleSheet("QPushButton{border: 0px;}");

    pocetni_izgled_ekrana();
}

Black_jack::~Black_jack()
{
    delete ui;
}

void Black_jack::pocetni_izgled_ekrana(){
    m_igrac->izbrisi();
    m_racunar.izbrisi();
    ui->ulog50->setVisible(false);
    ui->ulog100->setVisible(false);
    for(unsigned i = 0; i<m_spil.size(); i++){
        m_spil.pop_front();
    }

    odabran_ulog = false;
    m_ulog = 100;
    m_pobednik = 0;



    std::vector<QLabel *> vektor_labela = {ui->karta_igraca_1, ui->karta_igraca_2, ui->karta_igraca_3,
                                           ui->karta_igraca_4, ui->karta_igraca_5, ui->karta_igraca_6,
                                           ui->karta_racunara_1, ui->karta_racunara_2, ui->karta_racunara_3,
                                           ui->karta_racunara_4, ui->karta_racunara_5, ui->karta_racunara_6};

    for(unsigned i = 0; i<vektor_labela.size(); i++){
        vektor_labela.at(i)->clear();
        vektor_labela.at(i)->setVisible(false);
    }
    ui->novac->setNum(m_igrac->kredit());
    std::list<QLabel*> niz_labela_igrac = {ui->karta_igraca_1, ui->karta_igraca_2, ui->karta_igraca_3,
                                           ui->karta_igraca_4, ui->karta_igraca_5, ui->karta_igraca_6};
    std::list<QLabel*> niz_labela_racunar = {ui->karta_racunara_1, ui->karta_racunara_2, ui->karta_racunara_3,
                                               ui->karta_racunara_4, ui->karta_racunara_5, ui->karta_racunara_6};

    m_niz_labela_igrac = niz_labela_igrac;
    m_niz_labela_racunar = niz_labela_racunar;

    labela_ulog = new QLabel(this);
    labela_ulog->setVisible(false);

    labela_racunar = new QLabel(this);
    labela_racunar->setVisible(false);


    std::srand(unsigned(std::time(nullptr)));
    std::list<int> spil(m_karte.size());
    random_shuffle(m_karte.begin(), m_karte.end(), myrandom);
    std::copy(m_karte.begin(), m_karte.end(), spil.begin());

    ui->rezultat->setVisible(false);
    ui->sakrivena_karta->setVisible(false);
    m_spil = spil;
    ui->nova_igra->setVisible(false);
    ui->sledeca_karta->setVisible(false);
    ui->ne_zelim->setVisible(false);

}

template<typename T>
T Black_jack::uzmi_prvi_element(std::list<T>& spil){

    auto it = spil.begin();
    spil.pop_front();

    return *it;
}

void Black_jack::on_podeli_clicked(){


    if(m_igrac->kredit() > 0){
        proveri_ulog();
        for(unsigned i = 0; i<2; i++){
            QLabel* labela_igrac = uzmi_prvi_element(m_niz_labela_igrac);
            postavi_kartu(labela_igrac, "igrac");
        }
        for(unsigned i=0; i<2; i++){
            QLabel* labela_racunar = uzmi_prvi_element(m_niz_labela_racunar);
            postavi_kartu(labela_racunar, "racunar");
        }


        ui->karta_racunara_2->setText("");
        QPixmap pix(":/slike/karta.png");
        ui->sakrivena_karta->setPixmap(pix);
        ui->sakrivena_karta->setScaledContents(true);
        ui->sakrivena_karta->setVisible(true);

        deljenje_karata(ui->sakrivena_karta);

        ui->rezultat->setVisible(false);
        ui->sledeca_karta->setVisible(true);
        ui->ne_zelim->setVisible(true);
        ui->podeli->setVisible(false);
    }
    else{
        ui->rezultat->setText("Nemate vise kredita!");
        ui->rezultat->setVisible(true);
    }

}

void Black_jack::postavi_kartu(QLabel*& labela, std::string &&ko_igra){
    int rb_karte = uzmi_prvi_element(m_spil);

    if(ko_igra == "igrac"){
        m_igrac->dodaj_kartu(rb_karte%13 + 1);
    }
    else {
        m_racunar.dodaj_kartu(rb_karte%13 + 1);
    }
    QPixmap pix(napravi_putanju(rb_karte));

    labela->setPixmap(pix);
    labela->setScaledContents(true);
    if(m_racunar.broj_karata() == 2 and ko_igra == "racunar"){
        labela->setVisible(false);
    }
    else {
        labela->setVisible(true);
        deljenje_karata(labela);

    }
}

void Black_jack::deljenje_karata(QLabel*& labela){
    animacija = new QPropertyAnimation(labela, "geometry");
    animacija->setDuration(800);
    animacija->setStartValue(ui->spil->geometry());
    animacija->setEndValue(labela->geometry());
    animacija->start();
}


QString Black_jack::napravi_putanju(int rb_karte){
    int boja_karte = rb_karte%4;
    QString boja = "";
    if(boja_karte == 0)
        boja.append("tref");
    else if(boja_karte == 1)
        boja.append("pik");
    else if(boja_karte == 2)
        boja.append("herc");
    else {
        boja.append("karo");
    }

    int broj_karte = rb_karte%13+1;
    QString putanja = ":/slike/";
    std::string broj = std::to_string(broj_karte);
    QString karta = QString::fromUtf8(broj.c_str());
    QString putanja_do_karte = putanja.append(boja).append(karta).append(".png");

    return putanja_do_karte;
}

void Black_jack::on_back_clicked(){
    m_MainWindow->show();
    close();
}

void Black_jack::on_ne_zelim_clicked(){

    ui->sakrivena_karta->setVisible(false);
    ui->karta_racunara_2->setVisible(true);
    ui->sledeca_karta->setVisible(false);
    ui->rezultat->setVisible(true);
    ui->ne_zelim->setVisible(false);

    while(m_racunar.suma() <= 17){
        if(m_racunar.suma() > m_igrac->suma())
            break;
        QLabel* labela = uzmi_prvi_element(m_niz_labela_racunar);
        postavi_kartu(labela, "racunar");

    }

    if(m_igrac->suma() == 21){
        if((m_racunar.suma() == 21 and m_igrac->broj_karata() == 2 and m_racunar.broj_karata() != 2)
                or m_racunar.suma() != 21){
            m_igrac->izmeni_kredit(3*m_ulog);
            ui->rezultat->setText("POBEDLI STE!!!");
            m_pobednik = 1;

        }
    }
    else if(m_racunar.suma() > 21 || m_igrac->suma() > m_racunar.suma()){
        m_igrac->izmeni_kredit(2*m_ulog);
        ui->rezultat->setText("POBEDILI STE!!!");
        m_pobednik = 1;
    }
    else if(m_racunar.suma() > m_igrac->suma()){
        m_igrac->izmeni_kredit(-m_ulog);
        ui->rezultat->setText("Izgubili ste!");
    }
    else{
        ui->rezultat->setText("Nereseno");
        m_pobednik = 2;
    }

    provera_pobede();

    ui->nova_igra->setVisible(true);
    ui->sledeca_karta->setVisible(false);
    ui->ne_zelim->setVisible(false);


}

void Black_jack::on_sledeca_karta_clicked(){
    ui->ulog50->setVisible(false);
    ui->ulog100->setVisible(false);
    if(!odabran_ulog){
        QPixmap pix2(":/slike/cip100.png");
        kretanje_cipova(ui->cip100_2, ui->cip100, pix2, "igrac");
        kretanje_cipova(ui->pobedio_racunar, ui->racunar100, pix2, "racunar");
        odabran_ulog = true;
    }

    QLabel* labela = uzmi_prvi_element(m_niz_labela_igrac);
    postavi_kartu(labela, "igrac");
    if(m_igrac->suma() > 21){
        m_igrac->izmeni_kredit(-m_ulog);
        ui->rezultat->setVisible(true);
        ui->rezultat->setText("Izgubili ste!");
        ui->nova_igra->setVisible(true);
        ui->sledeca_karta->setVisible(false);
        ui->ne_zelim->setVisible(false);
        provera_pobede();

    }
}


void Black_jack::on_nova_igra_clicked(){

    ui->sledeca_karta->setVisible(false);
    ui->podeli->setVisible(true);
    labela_ulog->setVisible(false);
    labela_racunar->setVisible(false);
    pocetni_izgled_ekrana();
}

void Black_jack::on_ulog50_clicked(){
    QPixmap pix1(":/slike/cip50.png");
    QPixmap pix2(":/slike/cip100.png");

    kretanje_cipova(ui->cip50_2, ui->cip50, pix1, "igrac");
    kretanje_cipova(ui->pobedio_racunar, ui->racunar100, pix1, "racunar");
    m_ulog = 50;
    ui->ulog50->setVisible(false);
    ui->ulog100->setVisible(false);
    odabran_ulog = true;
}

void Black_jack::on_ulog100_clicked(){
    QPixmap pix1(":/slike/cip50.png");
    QPixmap pix2(":/slike/cip100.png");

    kretanje_cipova(ui->cip100_2, ui->cip100, pix2, "igrac");
    kretanje_cipova(ui->pobedio_racunar, ui->racunar100, pix2, "racunar");
    m_ulog = 100;

    ui->ulog50->setVisible(false);
    ui->ulog100->setVisible(false);
    odabran_ulog = true;

}

void Black_jack::kretanje_cipova(QLabel* &ko_salje, QLabel* &gde_saljem,
                                 QPixmap &pix, std::string&& ko_igra){

    if(ko_igra == "igrac"){
        labela_ulog->setPixmap(pix);
        labela_ulog->setScaledContents(true);
        labela_ulog->setVisible(true);

        animacija_za_cipove = new QPropertyAnimation(labela_ulog, "geometry");
        animacija_za_cipove->setDuration(600);
        animacija_za_cipove->setStartValue(ko_salje->geometry());
        animacija_za_cipove->setEndValue(gde_saljem->geometry());
        animacija_za_cipove->start();
    }
    else{
        labela_racunar->setPixmap(pix);
        labela_racunar->setScaledContents(true);
        labela_racunar->setVisible(true);

        animacija_za_cipove = new QPropertyAnimation(labela_racunar, "geometry");
        animacija_za_cipove->setDuration(800);
        animacija_za_cipove->setStartValue(ko_salje->geometry());
        animacija_za_cipove->setEndValue(gde_saljem->geometry());
        animacija_za_cipove->start();
    }
}


void Black_jack::proveri_ulog(){
    if(m_igrac->kredit()>= 100){
        ui->ulog50->setVisible(true);
        ui->ulog100->setVisible(true);
    }else if(m_igrac->kredit()>= 50){
        ui->ulog50->setVisible(true);
        ui->ulog100->setVisible(false);
    }
    else {
        ui->ulog50->setVisible(false);
        ui->ulog100->setVisible(false);
    }
}

void Black_jack::provera_pobede(){
    QPixmap pix1(":/slike/cip50.png");
    QPixmap pix2(":/slike/cip100.png");
    labela_ulog->setVisible(false);
    labela_racunar->setVisible(false);


    if(m_pobednik == 1){
        if(m_ulog == 50){
            kretanje_cipova(ui->cip50, ui->cip50_2, pix1, "igrac");
            kretanje_cipova(ui->racunar50, ui->cip50_2, pix1, "racunar");
        }
        else{
            kretanje_cipova(ui->cip100, ui->cip100_2, pix2, "igrac");
            kretanje_cipova(ui->racunar100, ui->cip100_2, pix2, "racunar");
        }
    }
    else if(m_pobednik == 0){
        if(m_ulog == 50){
            kretanje_cipova(ui->cip50, ui->pobedio_racunar, pix1, "igrac");
            kretanje_cipova(ui->racunar50, ui->pobedio_racunar, pix1, "racunar");
        }
        else{
            kretanje_cipova(ui->cip100, ui->pobedio_racunar, pix2, "igrac");
            kretanje_cipova(ui->racunar100, ui->pobedio_racunar, pix2, "racunar");
        }
    }
    else{
        if(m_ulog == 50){
            kretanje_cipova(ui->cip50, ui->cip50_2, pix1, "igrac");
            kretanje_cipova(ui->racunar50, ui->pobedio_racunar, pix1, "racunar");
        }
        else{
            kretanje_cipova(ui->cip100,  ui->cip100_2, pix2, "igrac");
            kretanje_cipova(ui->racunar100, ui->pobedio_racunar, pix2, "racunar");
        }

    }


}
