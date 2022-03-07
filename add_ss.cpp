#include "add_ss.h"
#include "ui_add_ss.h"
#include <QPushButton>
#include <QIntValidator>
Add_ss::Add_ss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_ss)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Oк");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    ui->line_height->setValidator(new QIntValidator(0, 999, this));
    ui->line_weight->setValidator(new QIntValidator(0, 999, this));
    qDebug()<<"aa";
}

Add_ss::~Add_ss()
{

    delete ui;
}
void Add_ss::on_buttonBox_accepted(){
    w = ui->line_height->text().toInt();
    qDebug()<<"aa"<<ui->line_height->text();
    qDebug()<<ui->line_weight->text().toInt();
    h = ui->line_weight->text().toInt();
}
