#include "slotgui.h"
#include "ui_slotgui.h"

SlotGui::SlotGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlotGui)
{
    ui->setupUi(this);
}

SlotGui::~SlotGui()
{
    delete ui;
}
