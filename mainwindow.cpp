#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    add_input_field();
    create_sample_sheet();
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
    connect(this, SIGNAL(check_complet()), this, SLOT(slot_edit_finished()));
    connect(list_ss[0], SIGNAL(triggered()), SLOT(add_sample_sheet()));
    connect(list_ss[1], SIGNAL(triggered()), SLOT(read_size_list_fsh()));
}

void MainWindow::slot_edit_finished(){
    if(!vec_form[vec_form.size() - 1].ln_nam->text().isEmpty() &&
            !vec_form[vec_form.size() - 1].ln_l->text().isEmpty() &&
            !vec_form[vec_form.size() - 1].ln_w->text().isEmpty() &&
            !vec_form[vec_form.size() - 1].ln_n->text().isEmpty())
    {
        add_input_field();
    }
}

void MainWindow::del_input_field(){
    if(vec_form.size() > 1){
        int n_form = vec_form.size();
        bool del_flg = false;
        for(int i = 0; i < n_form; i++){
            if(vec_form[i].butt_del->isChecked()){
                ui->vertical_layout->removeWidget(vec_form[i].frm);
                delete vec_form[i].butt_del;                        // Явное удаление формы
                delete vec_form[i].lbl_i;                           //
                delete vec_form[i].lbl_l;                           //
                delete vec_form[i].lbl_n;                           //
                delete vec_form[i].lbl_nam;                         //
                delete vec_form[i].lbl_w;                           //
                delete vec_form[i].ln_l;                            //
                delete vec_form[i].ln_nam;                          //
                delete vec_form[i].ln_w;                            //
                delete vec_form[i].ln_n;                            //
                delete vec_form[i].frm;                             // Явное удаление формы
                vec_form.remove(i);
                ui->vertical_layout->update();
                n_form--;
                del_flg = true;
            }
            if(vec_form.size() == i){ break; }
            if(del_flg){ vec_form[i].lbl_i->setText(QString::number(i + 1)); }
        }
    } else {
        vec_form[vec_form.size() - 1].butt_del->setChecked(false);
    }
    if(vec_form.size() == 1){
        emit check_complet();
    }
}

void MainWindow::add_input_field(){
    sample_form s_frm;

    s_frm.frm->setFixedSize(300, 120);
    s_frm.frm->setPalette(QPalette(Qt::black));
    s_frm.frm->setStyleSheet("QFrame { background-color: #B7CBD8 }");
    s_frm.frm->setFrameShape(QFrame::StyledPanel);

    s_frm.lbl_nam->setParent(s_frm.frm);
    s_frm.lbl_nam->setText("Имя");
    s_frm.lbl_nam->setGeometry(190, 30, 30, 16);

    s_frm.lbl_i->setParent(s_frm.frm);
    if(vec_form.isEmpty()){
        s_frm.lbl_i->setText("1.");
    } else {
        s_frm.lbl_i->setText(QString::number(vec_form.size() + 1) + ".");
    }
    s_frm.lbl_i->setFont(QFont("Segoe UI", 16));
    s_frm.lbl_i->setGeometry(2,50,20, 17);

    s_frm.lbl_l->setParent(s_frm.frm);
    s_frm.lbl_l->setText("Длина");
    s_frm.lbl_l->setGeometry(50, 60, 41, 16);

    s_frm.lbl_w->setParent(s_frm.frm);
    s_frm.lbl_w->setText("Ширина");
    s_frm.lbl_w->setGeometry(125, 60, 49, 16);

    s_frm.lbl_n->setParent(s_frm.frm);
    s_frm.lbl_n->setText("Кол-во");
    s_frm.lbl_n->setGeometry(210, 60, 49, 16);

    s_frm.ln_nam->setParent(s_frm.frm);
    s_frm.ln_nam->setGeometry(40, 30, 130, 22);
    connect(s_frm.ln_nam, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    s_frm.ln_l->setParent(s_frm.frm);
    s_frm.ln_l->setGeometry(40, 80, 60, 22);
    s_frm.ln_l->setValidator( new QIntValidator(0, 999, this) );
    connect(s_frm.ln_l, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    s_frm.ln_w->setParent(s_frm.frm);
    s_frm.ln_w->setGeometry(120, 80, 60, 22);
    s_frm.ln_w->setValidator( new QIntValidator(0, 999, this) );
    connect(s_frm.ln_w, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    s_frm.ln_n->setParent(s_frm.frm);
    s_frm.ln_n->setGeometry(200, 80, 60, 22);
    s_frm.ln_n->setValidator( new QIntValidator(0, 999, this) );
    connect(s_frm.ln_n, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    s_frm.butt_del->setParent(s_frm.frm);
    s_frm.butt_del->setCheckable(true);
    s_frm.butt_del->setFlat(true);
    s_frm.butt_del->setGeometry(270, 10, 21, 21);
    s_frm.butt_del->setIcon(QIcon(QPixmap(":/close.png").scaled(21,21)));

    vec_form.push_back(s_frm);

    connect(s_frm.butt_del, SIGNAL(clicked()), this, SLOT(del_input_field()));

    ui->vertical_layout->addWidget(s_frm.frm);

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
