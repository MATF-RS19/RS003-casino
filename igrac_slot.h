#ifndef IGRAC_SLOT_H
#define IGRAC_SLOT_H

#include "igrac.h"

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Igrac_slot :public Igrac
{
public:
    Igrac_slot(std::string ime = " ", int kredit = 1000);

    int karta() const;
    void dodaj_kartu(int karta);

private:
    int m_karta;

};

#endif // IGRAC_SLOT_H
