#include "igrac.h"

int Igrac::kredit() const{
    return m_kredit;
}

void Igrac::izmeni_kredit(int dobitak){
    m_kredit += dobitak;
}

int Igrac::zelim_da_igram() const{
    return m_zelim_da_igram;
}

void Igrac::izmeni_zelim_da_igram(){
    m_zelim_da_igram = false;
}
