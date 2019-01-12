#include "racunar_bj.h"
#include "igrac_bj.h"

Racunar_bj::Racunar_bj()
    {
    }


int Racunar_bj::suma(){
    std::stable_partition(m_karte_racunar.begin(), m_karte_racunar.end(), [] (int i) {return i%14 != 1;});
    return std::accumulate(m_karte_racunar.begin(), m_karte_racunar.end(), 0, provera);
}

void Racunar_bj::izbrisi(){
    m_karte_racunar.clear();
}

void Racunar_bj::dodaj_kartu(int karta){
        m_karte_racunar.push_back(karta);
}

size_t Racunar_bj::broj_karata() const{
    return m_karte_racunar.size();
}
