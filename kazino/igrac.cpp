#include "igrac.h"

Igrac::Igrac(std::string ime_igraca, int kredit)
    : m_ime_igraca(ime_igraca),
      m_kredit(kredit)
{
}

int Igrac::kredit() const{
    return m_kredit;
}

void Igrac::izmeni_kredit(int dobitak){
    m_kredit += dobitak;
}

void Igrac::postavi_ime(std::string ime){
    m_ime_igraca = ime;
}
void Igrac::postavi_kredit(int kredit){
    m_kredit = kredit;
}

std::string Igrac::ime(){
    return m_ime_igraca;
}
