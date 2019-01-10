#include "igrac_slot.h"

Igrac_slot::Igrac_slot(std::string ime, int kredit): Igrac(ime,kredit)
    {
    }
int Igrac_slot::karta() const{
    return m_karta;
}

void Igrac_slot::dodaj_kartu(int karta){
    m_karta = karta;
}



