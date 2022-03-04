#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
//#include <QtGui>
#include <QInputDialog>
#include <add_ss.h>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct sample_form{
    QFrame *frm = new QFrame;

    QLabel *lbl_nam = new QLabel;
    QLabel *lbl_i = new QLabel;
    QLabel *lbl_l = new QLabel;
    QLabel *lbl_w = new QLabel;
    QLabel *lbl_n = new QLabel;

    QLineEdit *ln_nam = new QLineEdit;
    QLineEdit *ln_l = new QLineEdit;
    QLineEdit *ln_w = new QLineEdit;
    QLineEdit *ln_n = new QLineEdit;

    QPushButton *butt_del = new QPushButton;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void check_complet();
private:
    void add_input_field();
    void create_sample_sheet();
    void paint_list_sheet(int w, int h);
    void paint_list_rects(QVector<QGraphicsRectItem *> rects, QVector<QGraphicsTextItem *>text_rects);
    void setstyle_list_text_rects(QGraphicsTextItem &text_rect, QGraphicsRectItem *rect);
    void clear();
private:
    QVector<sample_form> vec_form;
    QVector<QAction *> list_ss;
    QVector<QString> sheet_list_bd;
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsRectItem *sheetList = new QGraphicsRectItem();
    QVector<QGraphicsRectItem *> rects;
    QVector<QGraphicsTextItem *> text_rects;
    const size_t increase = 3;
    Ui::MainWindow *ui;

private slots:
    void del_input_field();
    void slot_edit_finished();
    void add_sample_sheet();
    void read_size_list_fsh();
};
#endif // MAINWINDOW_H
