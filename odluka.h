#ifndef ODLUKA_H
#define ODLUKA_H

#include <QDialog>
#include "igrac_slot.h"

namespace Ui {
class Odluka;
}

class Odluka : public QDialog
{
    Q_OBJECT

public:
    explicit Odluka(Igrac_slot& igrac, int poeni = 0, int ulog = 0);
    ~Odluka();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Igrac_slot *m_igrac;
    int m_poeni;
    int m_ulog;
    Ui::Odluka *ui;


};

#endif // ODLUKA_H
