#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_sample_sheet();
    connect(list_ss[0], SIGNAL(triggered()), SLOT(add_sample_sheet()));
    connect(list_ss[1], SIGNAL(triggered()), SLOT(read_size_list_fsh()));
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setScene(scene);
    scene->addItem(sheetList);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::create_sample_sheet(){
    QAction *plus = new QAction();
    QAction *a4 = new QAction();
    a4->setText("297 x 210");
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
        connect(list_ss[list_ss.size()-1], SIGNAL(triggered()), SLOT(read_size_list_fsh()));

    }

}
void MainWindow::add_sample_sheet(){
    Add_ss *dialog = new Add_ss;
    dialog->setFixedSize(200, 100);
    dialog->setWindowTitle("Создание шаблона");
    QString we_he;
    if(dialog->exec()){
        qDebug()<<"we = "<<dialog->w<<" he ="<<dialog->h;
        we_he = QString::number(dialog->h);
        we_he +=" x "+ QString::number(dialog->w);
    }
    QAction *sheet = new QAction();
    ui->menu->addAction(sheet);
    sheet->setText(we_he);
    list_ss.push_back(sheet);
    connect(list_ss[list_ss.size()-1], SIGNAL(triggered()), SLOT(read_size_list_fsh()));

}
void MainWindow::paint_list_sheet(int w, int h){
    ui->graphicsView->update();
    sheetList->setRect(0,0,w,h);
}
void MainWindow::read_size_list_fsh(){
    QObject *name = QObject::sender();
    QAction *sheet = qobject_cast<QAction*>(name);
    qDebug()<<sheet->text();
    QStringList we_he = sheet->text().split(" x ");
    qDebug()<<we_he[0].toInt()<<" "<<we_he[1].toInt();
    paint_list_sheet(we_he[0].toInt(),we_he[1].toInt());

}

