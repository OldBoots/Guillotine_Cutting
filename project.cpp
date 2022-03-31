#include "project.h"

Project::Project()
{
}
bool Project::file_open(bool read)
{
    if (!read) {
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "File open error";
            return 0;
        } else {
            qDebug() << "File open!";
        }
    } else {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "File open error";
            return 0;
        } else {
            qDebug() << "File open!";
        }
    }
    return 1;
}
bool Project::load(QVector<FormInfo>& vec_form_info, QVector<QVector<ProjectRect>>& vec_solution)
{
    QString file_text;
    path = QFileDialog::getOpenFileName(0, "Открыть проект", "", "*.json");
    if (!path.isEmpty()) {
        vec_form_info.clear();
        vec_solution.clear();
        file.setFileName(path);
        if (!file_open(true)) {
            return 0;
        }
        file_text = file.readAll();
        QJsonDocument docum = QJsonDocument::fromJson(file_text.toUtf8());
        QJsonObject jsonObject = docum.object();
        QJsonArray jsonArray = jsonObject["vec_form_info"].toArray();
        //Проходим по всем формам
        for (int j = 0; j < jsonArray.size(); j++) {
            QJsonValue value = jsonArray[j];
            vec_form_info.push_back(FormInfo(value["name"].toString(), value["width"].toInt(), value["length"].toInt(), value["numb"].toInt()));
        }
        QVector<ProjectRect> one_vec_sol;
        for (int i = 1; i < jsonObject.size(); i++) {
            one_vec_sol.clear();
            jsonArray = jsonObject["vec_solutions[" + QString::number(i - 1) + "]"].toArray();
            for (int j = 0; j < jsonArray.size(); j++) {
                QJsonValue value = jsonArray[j];
                one_vec_sol.push_back(ProjectRect(value["x"].toInt(), value["y"].toInt(), value["width"].toInt(), value["length"].toInt(), value["name"].toString()));
            }
            vec_solution.push_back(one_vec_sol);
        }
        file.close();
    } else {
        return 0;
    }
    return 1;
}
bool Project::saveAs(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution)
{
    path = QFileDialog::getSaveFileName(0, "Сохранение проекта", "", "*.json");
    if (!path.isEmpty()) {
        file.setFileName(path);
        if (!file_open()) {
            qDebug() << "file is_not open";
            return 0;
        }
        qDebug() << "file is open";
        save_vec_form_info(vec_form_info);
        save_vec_sol(vec_solution);
        doc.setObject(obj);
        file.write(doc.toJson());
        file.close();
    } else {
        qDebug() << "file no path open";
        return 0;
    }
    return 1;
}
bool Project::save(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution)
{
    if (!path.isEmpty()) {
        file.setFileName(path);
        if (!file_open()) {
            return 0;
        }
        save_vec_form_info(vec_form_info);
        save_vec_sol(vec_solution);
        //Считать формы
        doc.setObject(obj);
        file.write(doc.toJson());
        file.close();
    } else {
        qDebug() << "save_ass";
        saveAs(vec_form_info, vec_solution);
    }
    return 1;
}
void Project::save_vec_form_info(QVector<FormInfo> vec_form_info)
{
    QJsonObject form_info;
    QJsonArray arr_form_info;
    for (int i = 0; i < vec_form_info.size(); i++) {
        form_info.insert("name", vec_form_info[i].name());
        form_info.insert("width", vec_form_info[i].width());
        form_info.insert("length", vec_form_info[i].length());
        form_info.insert("numb", vec_form_info[i].numb());
        arr_form_info.append(form_info);
    }
    obj.insert("vec_form_info", arr_form_info);
}
void Project::save_vec_sol(QVector<QVector<ProjectRect>> vec_solution)
{
    QJsonObject form;
    for (int i = 0; i < vec_solution.size(); i++) {
        QJsonArray arr_form;
        for (int j = 0; j < vec_solution[i].size(); j++) {
            form.insert("name", vec_solution[i][j].name());
            form.insert("width", vec_solution[i][j].width());
            form.insert("length", vec_solution[i][j].length());
            form.insert("x", vec_solution[i][j].x());
            form.insert("y", vec_solution[i][j].y());
            arr_form.append(form);
        }
        obj.insert("vec_solutions[" + QString::number(i) + "]", arr_form);
    }
}
