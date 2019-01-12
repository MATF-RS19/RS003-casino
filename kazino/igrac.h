#ifndef IGRAC_H
#define IGRAC_H


#include <iostream>
#include <string>
#include <vector>


class Igrac
{
public:
    Igrac(std::string ime_igraca = " ", int kredit = 1000);

    void izmeni_kredit(int dobitak);

    void postavi_ime(std::string ime);
    void postavi_kredit(int kredit);
    int kredit() const;
    std::string ime();

private:
    std::string m_ime_igraca;
    int m_kredit;
};

#endif // IGRAC_H
