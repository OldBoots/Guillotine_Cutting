#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_sample_sheet();
    connect(list_ss[0], SIGNAL(triggered()), SLOT(add_sample_sheet()));
//    for(int i = 1; i < list_ss.size(); i++){
//        connect(list_ss[i], SIGNAL(triggered()), SLOT(read_size_list_fsh()));
//    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::create_sample_sheet(){
    QAction *plus = new QAction();
    QAction *a4 = new QAction();
    a4->setText("210 x 297");
    plus->setText("Добавить шаблон..");
    list_ss.push_back(plus);
    list_ss.push_back(a4);
    ui->menu->addAction(list_ss[0]);
    ui->menu->addAction(list_ss[1]);
    for(int i = 0; i< sheet_list_bd.size(); i++){
        QAction *sheet = new QAction();
        sheet->setText(sheet_list_bd[i]);
        list_ss.push_back(sheet);
        ui->menu->addAction(list_ss[list_ss.size()-1]);
    }

}
void MainWindow::add_sample_sheet(){
    Add_ss *dialog = new Add_ss;
    dialog->setFixedSize(200, 100);
    dialog->setWindowTitle("Создание шаблона");
    QString we_he;
    if(dialog->exec()){
        qDebug()<<"we = "<<dialog->w<<" he ="<<dialog->h;
        we_he = QString::number(dialog->w);
        we_he +=" x "+ QString::number(dialog->h);
    }
    QAction *sheet = new QAction();
    ui->menu->addAction(sheet);
    sheet->setText(we_he);
    list_ss.push_front(sheet);

}
//void MainWindow::read_size_list_fsh(){
//    qDebug()<<name;
//    QStringList we_he;
//    we_he = name.split(" x ");
//    qDebug()<<we_he[0].toInt()<<" "<<we_he[1].toInt();

//}
