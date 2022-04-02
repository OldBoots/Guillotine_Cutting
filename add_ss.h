#ifndef ADD_SS_H
#define ADD_SS_H

#include <QDialog>

namespace Ui {
class Add_ss;
}

class Add_ss : public QDialog { // Диалоговое окно для добавления шаблона
    Q_OBJECT

public:
    explicit Add_ss(QWidget* parent = nullptr);
    ~Add_ss();
    int w();
    int l();

private:
    Ui::Add_ss* ui;
    int length;
    int width;

private slots:
    void on_buttonBox_accepted();
};

#endif // ADD_SS_H
