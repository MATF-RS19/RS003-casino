#ifndef IGRAC_BJ_H
#define IGRAC_BJ_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

#include "igrac.h"

int provera(int acc, int x);

class Igrac_bj :public Igrac
{
public:
    Igrac_bj(std::string ime = "Untilted", int kredit = 1000);

    int suma();
    void dodaj_kartu(int karta);
    size_t broj_karata() const;
    void izbrisi();

private:
    std::vector<int> m_karte_igrac;
};

#endif // IGRAC_BJ_H
