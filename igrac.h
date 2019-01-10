#ifndef IGRAC_H
#define IGRAC_H


#include <iostream>
#include <string>
#include <vector>


class Igrac
{
public:
    Igrac(std::string ime_igraca = " ", int kredit = 1000);
    int kredit() const;

    void izmeni_kredit(int dobitak);

    int zelim_da_igram() const;

    void izmeni_zelim_da_igram();

private:
    std::string m_ime_igraca;
    int m_kredit;
    bool m_zelim_da_igram = true;
};

#endif // IGRAC_H
