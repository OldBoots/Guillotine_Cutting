#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QInputDialog>
#include <add_ss.h>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void create_sample_sheet();
    QVector<QAction *> list_ss;
    QVector<QString> sheet_list_bd;
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsRectItem *sheetList = new QGraphicsRectItem();
    QVector<QGraphicsRectItem *> rects;
    QVector<QGraphicsTextItem *> text_rects;
    void paint_list_sheet(int w, int h);
    void paint_list_rects(QVector<QGraphicsRectItem *> rects, QVector<QGraphicsTextItem *>text_rects);
    void setstyle_list_text_rects(QGraphicsTextItem &text_rect, QGraphicsRectItem *rect);
    void clear();
    const size_t increase = 3;
private slots:
    void add_sample_sheet();
    void read_size_list_fsh();
};
#endif // MAINWINDOW_H
