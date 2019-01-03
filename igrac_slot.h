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
#include <list>

class Igrac_slot : public Igrac
{
public:
    Igrac_slot(std::string ime, int kredit)
        : Igrac(ime,kredit){}

    void promeni_manja_veca();

    bool manja_veca() const;

private:
    bool m_manja_veca = false;
};

#endif // IGRAC_SLOT_H
