#include "igrac_slot.h"

void Igrac_slot::promeni_manja_veca(){
    m_manja_veca = !m_manja_veca;
}

bool Igrac_slot::manja_veca() const{
    return m_manja_veca;
}
