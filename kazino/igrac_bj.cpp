#include "igrac_bj.h"

Igrac_bj::Igrac_bj(std::string ime, int kredit) : Igrac(ime, kredit)
    {
    }

int provera(int acc, int x){
    if(x != 1 && x <= 10){
        acc += x;
    }
    else if(x > 10){
        acc += 10;
    }
    else{
        if(acc <= 10 )
            acc += 11;
        else {
            acc += 1;
        }
    }
    return acc;
}

int Igrac_bj::suma(){
    std::stable_partition(m_karte_igrac.begin(), m_karte_igrac.end(), [] (int i){return i % 13 != 1;});
    return std::accumulate(m_karte_igrac.begin(), m_karte_igrac.end(), 0, provera);
}

void Igrac_bj::dodaj_kartu(int karta){
    m_karte_igrac.push_back(karta);
}

void Igrac_bj::izbrisi(){
    m_karte_igrac.clear();
}


size_t Igrac_bj::broj_karata() const{
    return m_karte_igrac.size();
}

