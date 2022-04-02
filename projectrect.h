#ifndef PROJECTRECT_H
#define PROJECTRECT_H

#include <QPoint>
#include <QString>

class ProjectRect { // Параметры заготовки.
    QString r_name;
    QPoint r_top;
    int r_length;
    int r_width;
    bool r_added;
    bool r_turn;

public:
    ProjectRect(QPoint top, int width, int length, QString name = QString(), bool added = false);
    ProjectRect(int x, int y, int width, int length, QString name = QString(), bool added = false);
    ProjectRect();
    QString name();
    QPoint top();
    int x();
    int y();
    int length();
    int width();
    bool added();
    bool turn();
    void set_turn(bool turn);
    void set_added(bool added);
    void set_top(QPoint top);
    void set_top(int x, int y);
    void operator=(ProjectRect other);
};

#endif // PROJECTRECT_H
