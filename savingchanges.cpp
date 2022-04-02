#include "savingchanges.h"
#include "ui_savingchanges.h"

SavingChanges::SavingChanges(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SavingChanges)
{
    ui->setupUi(this);
    connect(ui->butt_yes, SIGNAL(clicked()), this, SLOT(slot_yes()));
    connect(ui->butt_no, SIGNAL(clicked()), this, SLOT(slot_no()));
    connect(ui->butt_cancel, SIGNAL(clicked()), this, SLOT(slot_cancel()));
}

void SavingChanges::slot_yes()
{
    flag = 1;
    this->accept();
}

void SavingChanges::slot_no()
{
    flag = 0;
    this->accept();
}

void SavingChanges::slot_cancel()
{
    flag = -1;
    this->accept();
}

int SavingChanges::exec_flag()
{
    return flag;
}

SavingChanges::~SavingChanges()
{
    delete ui;
}
