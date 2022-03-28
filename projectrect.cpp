#include "projectrect.h"

ProjectRect::ProjectRect(){

}

ProjectRect::ProjectRect(int x, int y, int width, int length, QString name, bool added){
    r_top = QPoint(x, y);
    r_width = width;
    r_length = length;
    r_name = name;
    r_added = added;
    r_turn = false;
}

ProjectRect::ProjectRect(QPoint top, int width, int length, QString name, bool added){
    r_top = top;
    r_width = width;
    r_length = length;
    r_name = name;
    r_added = added;
    r_turn = false;
}

void ProjectRect::operator=(ProjectRect other){
    this->r_top = other.r_top;
    this->r_width = other.r_width;
    this->r_length = other.r_length;
    this->r_name = other.r_name;
    this->r_turn = other.r_turn;
}

void ProjectRect::set_added(bool added){
    r_added = added;
}

void ProjectRect::set_turn(bool turn){
    r_turn = turn;
}

void ProjectRect::set_top(QPoint top){
    r_top = top;
}

void ProjectRect::set_top(int x, int y){
    r_top = QPoint(x, y);
}

int ProjectRect::x(){
    return r_top.x();
}

int ProjectRect::y(){
    return r_top.y();
}

bool ProjectRect::added(){
    return r_added;
}

bool ProjectRect::turn(){
    return r_turn;
}

QString ProjectRect::name(){
    return r_name;
}

QPoint ProjectRect::top(){
    return r_top;
}

int ProjectRect::length(){
    if(!r_turn) {
        return r_length;
    } else {
        return r_width;
    }
}

int ProjectRect::width(){
    if(!r_turn) {
        return r_width;
    } else {
        return r_length;
    }
}
