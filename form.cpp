#include "form.h"

Form::Form(int length, int width){
    this->f_length = length;
    this->f_width = width;
}

Form::Form(QSize size){
    this->f_length = size.height();
    this->f_width = size.width();
}

Form::Form(QString name, int length, int width, int n_form){
    this->f_name = name;
    this->f_length = length;
    this->f_width = width;
    this->f_n_form = n_form;
}

QSize Form::get_size(){
    return QSize(f_width, f_length);
}

QString Form::name(){
    return f_name;
}

int Form::numb(){
    return f_n_form;
}

int Form::length(){
    return f_length;
}

int Form::width(){
    return f_width;
}

Form::~Form(){}
