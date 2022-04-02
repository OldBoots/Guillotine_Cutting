#ifndef PROJECT_H
#define PROJECT_H
#include "form.h"
#include "projectrect.h"
#include <QAction>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QStringList>
class Project {

public:
    Project();
    bool save(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution); //Сохранение проекта в файл по заданному пути
    bool saveAs(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution, bool save_flag = false); //Сохрание проекта в файл с выбором пути
    bool load(QVector<FormInfo>& vec_form_info, QVector<QVector<ProjectRect>>& vec_solution); //Загрузка проекта из файла
    bool save_samples(QVector<QAction*> vec_sample_sheets); //Сохранение шаблонов в файл
    bool load_samples(QVector<QAction*>& vec_sample_sheets); //Загрузка шаблонов из файла

public:
    QString path_projects;
    QString path_sample = QDir::currentPath() + "//sample.json";

private:
    QFile file;
    QJsonDocument doc;
    QJsonObject obj;

private:
    bool file_open(bool read = false);
    void save_vec_form_info(QVector<FormInfo> vec_form_info);
    void save_vec_sol(QVector<QVector<ProjectRect>> vec_solution);
};

#endif // PROJECT_H
