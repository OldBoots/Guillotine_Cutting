#include "form.h"

FormInfo::FormInfo(int length, int width){
    f_length = length;
    f_width = width;
    f_turn = false;
}

FormInfo::FormInfo(QSize size){
    f_length = size.height();
    f_width = size.width();
    f_turn = false;
}

FormInfo::FormInfo(QString name, int length, int width, int n_form){
    f_name = name;
    f_length = length;
    f_width = width;
    f_n_form = n_form;
    f_turn = false;
}

QSize FormInfo::get_size(){
    return QSize(f_width, f_length);
}

QString FormInfo::name(){
    return f_name;
}

int FormInfo::numb(){
    return f_n_form;
}

int FormInfo::length(){
    return f_length;
}

int FormInfo::width(){
    return f_width;
}

bool FormInfo::turn(){
    return f_turn;
}
void FormInfo::set_turn(bool turn){
    f_turn = turn;
}

FormInfo::~FormInfo(){}
