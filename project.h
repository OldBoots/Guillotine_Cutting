#ifndef PROJECT_H
#define PROJECT_H
#include "form.h"
#include "projectrect.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class Project {
private:
    QFile file;
    QJsonDocument doc;
    QJsonObject obj;
    QString path;

public:
    Project();
    bool save(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution);
    bool saveAs(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution);
    bool load(QVector<FormInfo>& vec_form_info, QVector<QVector<ProjectRect>>& vec_solution);
    void save_vec_form_info(QVector<FormInfo> vec_form_info);
    void save_vec_sol(QVector<QVector<ProjectRect>> vec_solution);

private:
    bool file_open(bool read = false);
};

#endif // PROJECT_H
