#include "add_ss.h"
#include "ui_add_ss.h"
#include <QPushButton>
#include <QIntValidator>
Add_ss::Add_ss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_ss)
{
    ui->setupUi(this);
    this->setFixedSize(200, 100);
    this->setWindowTitle("Создание шаблона");
    length = width = 0;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Oк");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    ui->line_height->setValidator(new QIntValidator(0, 999, this));
    ui->line_weight->setValidator(new QIntValidator(0, 999, this));
}

Add_ss::~Add_ss(){
    delete ui;
}

int Add_ss::w(){
    return width;
}

int Add_ss::l(){
    return length;
}

void Add_ss::on_buttonBox_accepted(){
    width = ui->line_height->text().toInt();
    length = ui->line_weight->text().toInt();
}
