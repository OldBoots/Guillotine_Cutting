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
    QGraphicsRectItem *_rect = new QGraphicsRectItem();
    QGraphicsRectItem *_rect1 = new QGraphicsRectItem();
    QGraphicsTextItem *text = new QGraphicsTextItem[2];
    _rect->setRect(0*increase,0*increase,100*increase,50*increase);
    text[0].setPlainText("name\n100 x 50");
    text[1].setPlainText("name65442\n10 x 10");
    text_rects<<&text[0];
    text_rects<<&text[1];
    rects<<_rect;
    _rect1->setRect(0*increase,40*increase,20*increase,20*increase);
    rects<<_rect1;
    paint_list_rects(rects, text_rects);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::clear(){
    for(int i = 0; i < rects.size(); i++){
     scene->removeItem(rects[i]);
     scene->removeItem(text_rects[i]);
     }
     scene->update();
     ui->graphicsView->update();
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
    sheetList->setRect(0,0,w*increase,h*increase);
}
void MainWindow::read_size_list_fsh(){
    qDebug()<<scene->items().size();
    clear();
    qDebug()<<scene->items().size();

    QObject *name = QObject::sender();
    QAction *sheet = qobject_cast<QAction*>(name);
    qDebug()<<sheet->text();
    QStringList we_he = sheet->text().split(" x ");
    qDebug()<<we_he[0].toInt()<<" "<<we_he[1].toInt();
    paint_list_sheet(we_he[0].toInt(),we_he[1].toInt());


}
void MainWindow::setstyle_list_text_rects(QGraphicsTextItem &text_rect, QGraphicsRectItem *rect){
    qreal x_rect, y_rect, w_rect,h_rect;
    QRectF getposrect;
    getposrect = rect->rect();
    getposrect.getRect(&x_rect, &y_rect, &w_rect, &h_rect);
    text_rect.setPos(x_rect+1, y_rect+1);
    text_rect.setTextWidth(w_rect);
    QFont font;
    font.setPixelSize((w_rect+h_rect)/15);
    text_rect.setFont(font);
}
void MainWindow::paint_list_rects(QVector<QGraphicsRectItem *> rects, QVector<QGraphicsTextItem *>text_rects){

    for(int i = 0; i < rects.size(); i++){
       if(i == 0){
           scene->addItem(rects[i]);
           setstyle_list_text_rects(*text_rects[i], rects[i]);
           scene->addItem(text_rects[i]);
       } else{
           for(int j = i-1; j>=0; j--){
                scene->addItem(rects[i]);

               if(rects[i]->rect().intersects(rects[j]->rect())){
                   qDebug()<<"intersect Rect["<<j<<"] Rect["<<i<<"]";
               }

               setstyle_list_text_rects(*text_rects[i], rects[i]);
               scene->addItem(text_rects[i]);
           }
       }
    }
}
