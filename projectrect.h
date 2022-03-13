#ifndef PROJECTRECT_H
#define PROJECTRECT_H

#include <QPoint>
#include <QString>

class ProjectRect{        // Параметры заготовки.
    QString r_name;
    QPoint r_top;
    int r_length;
    int r_width;
public:
    ProjectRect(QPoint top, int width, int length, QString name = QString());
    ProjectRect(int x, int y, int width, int length, QString name = QString());
    ProjectRect();
    QString name();
    QPoint top();
    int x();
    int y();
    int length();
    int width();
    void set_top(QPoint top);
    void set_top(int x, int y);
    void operator=(ProjectRect other);
};

#endif // PROJECTRECT_H
