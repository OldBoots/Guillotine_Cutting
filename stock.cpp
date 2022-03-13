#include "stock.h"

Stock::Stock(int x, int y, int width, int length){
    s_top = QPoint(x, y);
    s_length = length;
    s_width = width;
}

Stock::Stock(QPoint top, int width, int length){
    s_top = top;
    s_length = length;
    s_width = width;
}

QPoint Stock::top(){
return s_top;
}

int Stock::length(){
return s_length;
}

int Stock::width(){
return s_width;
}
