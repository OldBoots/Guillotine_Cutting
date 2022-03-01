#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QInputDialog>
#include <add_ss.h>

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
private slots:
    void add_sample_sheet();
   // void read_size_list_fsh();
};
#endif // MAINWINDOW_H
