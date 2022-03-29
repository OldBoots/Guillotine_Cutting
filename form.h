#ifndef FORM_H
#define FORM_H

#include <QString>
#include <QSize>

class FormInfo{         // Параметры формы.
private:
    QString f_name;
    int f_length;
    int f_width;
    int f_n_form;
    bool f_turn;
public:
    FormInfo(int length, int width);
    FormInfo(QString name, int length, int width, int n_form);
    FormInfo(QSize size);
    ~FormInfo();
    QSize get_size();
    QString name();
    int length();
    int width();
    int numb();
    bool turn();
    void set_turn(bool turn);
};

#endif // FORM_H
