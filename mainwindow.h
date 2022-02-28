#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

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
private:
    QVector<sample_form> vec_form;
    Ui::MainWindow *ui;
private slots:
    void del_input_field();
    void slot_edit_finished();
};
#endif // MAINWINDOW_H
