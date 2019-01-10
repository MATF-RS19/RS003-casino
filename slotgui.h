#ifndef SLOTGUI_H
#define SLOTGUI_H

#include <QDialog>
#include "slot.h"

namespace Ui {
class SlotGui;
}

class SlotGui : public QDialog, Slot
{
    Q_OBJECT

public:
    explicit SlotGui(QWidget *parent = nullptr);
    ~SlotGui();

private:
    Ui::SlotGui *ui;
};

#endif // SLOTGUI_H
