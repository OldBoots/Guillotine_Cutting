#ifndef STOCK_H
#define STOCK_H

#include <QPoint>

class Stock { // Параметры заготовки.
    QPoint s_top;
    int s_length;
    int s_width;

public:
    Stock(QPoint top, int width, int length);
    Stock(int x, int y, int width, int length);
    QPoint top();
    int length();
    int width();
};

#endif // STOCK_H
