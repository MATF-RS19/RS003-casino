#ifndef RACUNAR_BJ_H
#define RACUNAR_BJ_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

class Racunar_bj
{
public:
    Racunar_bj();

    int suma();

    void izbrisi();
    size_t broj_karata() const;
    void dodaj_kartu(int karta);

private:
    std::vector<int> m_karte_racunar;
};

#endif // RACUNAR_BJ_H
