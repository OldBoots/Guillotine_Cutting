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
    connect(this, SIGNAL(sig_check_complet()), this, SLOT(slot_edit_finished()));
    connect(list_ss[0], SIGNAL(triggered()), SLOT(slot_add_sample_sheet()));
    connect(list_ss[1], SIGNAL(triggered()), SLOT(slot_read_size_list_fsh()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_run()));
    connect(this, SIGNAL(sig_error(QString)), this, SLOT(slot_error(QString)));
}

void MainWindow::add_stock_in_vec(Stock cur_stock){
    vec_stok << cur_stock;
    for (int i = vec_stok.size() - 1; i > 0 ; i--) {
        if(vec_stok[i].width() < vec_stok[i - 1].width()){
            qSwap(vec_stok[i], vec_stok[i - 1]);
        } else if (vec_stok[i].width() == vec_stok[i - 1].width() &&
                   vec_stok[i].length() < vec_stok[i - 1].length()){
            qSwap(vec_stok[i], vec_stok[i - 1]);
        } else { break; }
    }
}

void MainWindow::recursive_cutting(){
    for (int i = 0; i < vec_stok.size(); i++) {

    }
}

void MainWindow::slot_error(QString error_massage){
    QStringList message = error_massage.split("_");
    error_code = message[1];
    ui->statusbar->showMessage(message[0]);
}

void MainWindow::slot_run(){
    if(!vec_form.isEmpty()){ vec_form.clear(); }
    if(!ui->statusbar->currentMessage().isEmpty()){ ui->statusbar->clearMessage(); error_code.clear(); }
    vec_stok << Stock(0, 0, currnet_sheet.width(), currnet_sheet.height());
    int area_sheet, area_general = 0;
    area_sheet = currnet_sheet.width() * currnet_sheet.height();
    for (int i = 0; i < vec_frame.size() - 1; i++) {
        Form form(vec_frame[i]->findChild<QLineEdit *>("ln_name")->text(),
                  vec_frame[i]->findChild<QLineEdit *>("ln_length")->text().toInt(),
                  vec_frame[i]->findChild<QLineEdit *>("ln_width")->text().toInt(),
                  vec_frame[i]->findChild<QLineEdit *>("ln_number")->text().toInt());
        if(vec_frame[i]->findChild<QLineEdit *>("ln_length")->text().isEmpty() ||
                vec_frame[i]->findChild<QLineEdit *>("ln_width")->text().isEmpty() ||
                vec_frame[i]->findChild<QLineEdit *>("ln_number")->text().isEmpty()){
            emit sig_error("Ворма \"" + form.name() + "\" задана неверно._S1");
            return;
        }
        if((currnet_sheet.width() < form.width() || currnet_sheet.height() < form.length())){
            emit sig_error("Форма \"" + form.name() + "\" не входит на лист._S2");
            return;
        }
        area_general += form.width() * form.length() * form.numb();
        vec_form << form;
        for (int j = i; j > 0; j--){
            if(vec_form[j].width() > vec_form[j - 1].width()){
                qSwap(vec_form[j], vec_form[j - 1]);
            } else if(vec_form[j].width() == vec_form[j - 1].width() &&
                      vec_form[j].length() > vec_form[j - 1].length()){
                qSwap(vec_form[j], vec_form[j - 1]);
            } else { break; }
        }
    }
    if(area_sheet < area_general){
        emit sig_error("Общая площадь форм больше площади листа._S3");
        return;
    }
    for (int i = 0; i < vec_form.size(); i++) {
        qDebug() << vec_form[i].width() << " x " << vec_form[i].length();
    }

}

void MainWindow::slot_edit_finished(){
    if(!vec_frame[vec_frame.size() - 1]->findChild<QLineEdit *>("ln_name")->text().isEmpty() &&
            !vec_frame[vec_frame.size() - 1]->findChild<QLineEdit *>("ln_length")->text().isEmpty() &&
            !vec_frame[vec_frame.size() - 1]->findChild<QLineEdit *>("ln_width")->text().isEmpty() &&
            !vec_frame[vec_frame.size() - 1]->findChild<QLineEdit *>("ln_number")->text().isEmpty())
    {
        add_input_field();
    }
}

void MainWindow::slot_del_input_field(){
    if(vec_frame.size() > 1){
        int n_form = vec_frame.size();
        bool del_flg = false;
        for(int i = 0; i < n_form; i++){
            if(vec_frame[i]->findChild<QPushButton *>("butt_del")->isChecked()){
                ui->vertical_layout->removeWidget(vec_frame[i]);
                delete vec_frame[i];
                vec_frame.remove(i);
                ui->vertical_layout->update();
                n_form--;
                del_flg = true;
            }
            if(vec_frame.size() == i){ break; }
            if(del_flg){ vec_frame[i]->findChild<QLabel *>("lbl_index")->setText(QString::number(i + 1)); }
        }
    } else {
        vec_frame[vec_frame.size() - 1]->findChild<QPushButton *>("butt_del")->setChecked(false);
    }
    if(vec_frame.size() == 1){
        emit sig_check_complet();
    }
}

void MainWindow::add_input_field(){
    vec_frame << new QFrame(this);
    QLabel *lbl_length = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLabel *lbl_width = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLabel *lbl_index = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLabel *lbl_number = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLabel *lbl_name = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLineEdit *ln_length = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_length->setObjectName("ln_length");
    QLineEdit *ln_width = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_width->setObjectName("ln_width");
    QLineEdit *ln_number = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_number->setObjectName("ln_number");
    QLineEdit *ln_name = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_name->setObjectName("ln_name");
    QPushButton *butt_del = new QPushButton(vec_frame[vec_frame.size() - 1]);
    butt_del->setObjectName("butt_del");

    vec_frame[vec_frame.size() - 1]->setFixedSize(300, 120);
    vec_frame[vec_frame.size() - 1]->setStyleSheet("QFrame { background-color: #B7CBD8 }");
    vec_frame[vec_frame.size() - 1]->setFrameShape(QFrame::StyledPanel);

    lbl_name->setText("Имя");
    lbl_name->setGeometry(190, 30, 30, 16);

    lbl_index->setText(QString::number(vec_frame.size()) + ".");
    QFont font;
    font.setPixelSize(16);
    lbl_index->setFont(font);
    lbl_index->setGeometry(2,50,20, 17);

    lbl_length->setText("Длина");
    lbl_length->setGeometry(50, 60, 41, 16);

    lbl_width->setText("Ширина");
    lbl_width->setGeometry(125, 60, 49, 16);

    lbl_number->setText("Кол-во");
    lbl_number->setGeometry(210, 60, 49, 16);

    ln_name->setGeometry(40, 30, 130, 22);
    connect(ln_name, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    ln_length->setGeometry(40, 80, 60, 22);
    ln_length->setValidator( new QIntValidator(0, 999, this) );
    connect(ln_length, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    ln_width->setGeometry(120, 80, 60, 22);
    ln_width->setValidator( new QIntValidator(0, 999, this) );
    connect(ln_width, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    ln_number->setGeometry(200, 80, 60, 22);
    ln_number->setValidator( new QIntValidator(0, 999, this) );
    connect(ln_number, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    butt_del->setCheckable(true);
    butt_del->setFlat(true);
    butt_del->setGeometry(270, 10, 21, 21);
    butt_del->setIcon(QIcon(QPixmap(":/close.png").scaled(21,21)));

    connect(butt_del, SIGNAL(clicked()), this, SLOT(slot_del_input_field()));

    ui->vertical_layout->addWidget(vec_frame[vec_frame.size() - 1]);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::clear_scene(){
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
        connect(list_ss[list_ss.size()-1], SIGNAL(triggered()), SLOT(slot_read_size_list_fsh()));

    }

}
void MainWindow::slot_add_sample_sheet(){
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
    connect(list_ss[list_ss.size()-1], SIGNAL(triggered()), SLOT(slot_read_size_list_fsh()));

}
void MainWindow::paint_list_sheet(int w, int h){
    ui->graphicsView->update();
    sheetList->setRect(0,0,w*increase,h*increase);
    currnet_sheet = QSize(w, h);
}
void MainWindow::slot_read_size_list_fsh(){
    qDebug()<<scene->items().size();
    clear_scene();
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
