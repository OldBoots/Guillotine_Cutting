#ifndef FORM_H
#define FORM_H

#include <QString>
#include <QSize>

class Form{         // Параметры формы.
private:
    QString f_name;
    int f_length;
    int f_width;
    int f_n_form;
public:
    Form(int length, int width);
    Form(QString name, int length, int width, int n_form);
    Form(QSize size);
    ~Form();
    QSize get_size();
    QString name();
    int length();
    int width();
    int numb();
};

#endif // FORM_H
