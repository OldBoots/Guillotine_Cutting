#include "projectrect.h"

ProjectRect::ProjectRect(){

}

bool ProjectRect::added(){
    return r_added;
}

void ProjectRect::set_added(bool added){
    r_added = added;
}


ProjectRect::ProjectRect(int x, int y, int width, int length, QString name, bool added){
    r_top = QPoint(x, y);
    r_width = width;
    r_length = length;
    r_name = name;
    r_added = added;
}

ProjectRect::ProjectRect(QPoint top, int width, int length, QString name, bool added){
    r_top = top;
    r_width = width;
    r_length = length;
    r_name = name;
    r_added = added;
}

void ProjectRect::operator=(ProjectRect other){
    this->r_top = other.r_top;
    this->r_width = other.r_width;
    this->r_length = other.r_length;
    this->r_name = other.r_name;
}

int ProjectRect::x(){
    return r_top.x();
}

int ProjectRect::y(){
    return r_top.y();
}

void ProjectRect::set_top(QPoint top){
    r_top = top;
}

void ProjectRect::set_top(int x, int y){
    r_top = QPoint(x, y);
}



QString ProjectRect::name(){
    return r_name;
}

QPoint ProjectRect::top(){
    return r_top;
}

int ProjectRect::length(){
    return r_length;
}

int ProjectRect::width(){
    return r_width;
}
