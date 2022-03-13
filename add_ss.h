#ifndef ADD_SS_H
#define ADD_SS_H

#include <QDialog>

namespace Ui {
class Add_ss;
}

class Add_ss : public QDialog{          // Диалоговое окно для добавления шаблона
    Q_OBJECT

public:
    explicit Add_ss(QWidget *parent = nullptr);
    int w = 0;
    int h = 0;
    ~Add_ss();

private:
    Ui::Add_ss *ui;
private slots:
    void on_buttonBox_accepted();
};

#endif // ADD_SS_H
