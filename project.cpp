#include "project.h"

Project::Project()
{
}
bool Project::file_open(bool read)
{
    //Открытие файла для чтения или записи
    if (read) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return 0;
        } else {
        }
    } else {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return 0;
        }
    }
    return 1;
}
bool Project::load(QVector<FormInfo>& vec_form_info, QVector<QVector<ProjectRect>>& vec_solution)
{
    //Получаем путь к проекту
    path_projects = QFileDialog::getOpenFileName(0, "Открыть проект", "", "*.json");
    //Если выбор был сделан
    if (!path_projects.isEmpty()) {
        //Очистка полей проекта перед загрузкой
        vec_form_info.clear();
        vec_solution.clear();
        //Открываем файл для чтения
        file.setFileName(path_projects);
        if (!file_open(true)) {
            return 0;
        }
        //Считываем весь текст из файла в строку
        QString file_text;
        file_text = file.readAll();
        //Преобразум строку в jsondocument
        QJsonDocument docum = QJsonDocument::fromJson(file_text.toUtf8());
        QJsonObject jsonObject = docum.object();
        //Находим нужный массив по ключу
        QJsonArray jsonArray = jsonObject["vec_form_info"].toArray();
        //Проходим по всем формам и записываем данные в vec_form_info
        for (int j = 0; j < jsonArray.size(); j++) {
            QJsonValue value = jsonArray[j];
            vec_form_info.push_back(FormInfo(value["name"].toString(), value["width"].toInt(), value["length"].toInt(), value["numb"].toInt()));
        }
        //Проходим по всем вариантам компоновки и записываем их в vec_solution
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
bool Project::saveAs(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution, bool save_flag)
{
    //Если необходимо указать путь, указываем
    if (save_flag) {
        if (path_projects.isEmpty()) {
            path_projects = QFileDialog::getSaveFileName(0, "Сохранение проекта", QDir::currentPath() + "//Projects//unnamed.json", "*.json");
        }
    } else {

        path_projects = QFileDialog::getSaveFileName(0, "Сохранение проекта", QDir::currentPath() + "//Projects//unnamed.json", "*.json");
    }
    //Сохраняем в файл информацию о формах и их варианты компоновок
    save(vec_form_info, vec_solution);
    return 1;
}
bool Project::save(QVector<FormInfo> vec_form_info, QVector<QVector<ProjectRect>> vec_solution)
{
    //Сохранение данных проекта в файл
    if (!path_projects.isEmpty()) {
        file.setFileName(path_projects);
        if (!file_open()) {
            return 0;
        }
        save_vec_form_info(vec_form_info);
        save_vec_sol(vec_solution);
        doc.setObject(obj);
        file.write(doc.toJson());
        file.close();
    }
    return 1;
}
void Project::save_vec_form_info(QVector<FormInfo> vec_form_info)
{
    //Проходим по формам и записываем данные о них
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
    //Проходим по всем вариантам компоновки и записываем их
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
bool Project::save_samples(QVector<QAction*> vec_sample_sheets)
{
    QJsonDocument doc;
    QJsonObject obj;
    QJsonObject sample;
    QJsonArray arr_form;
    //Открываем файл
    file.setFileName(path_sample);
    if (!file_open()) {
        return 0;
    }
    //Проходим по всем шаблонам и сохраняем их в файл
    QStringList data_sample;
    for (int i = 0; i < vec_sample_sheets.size(); i++) {
        data_sample = vec_sample_sheets[i]->text().split(" x ");
        sample.insert("width", data_sample[0]);
        sample.insert("length", data_sample[1]);
        arr_form.append(sample);
    }
    obj.insert("sample_sheet", arr_form);
    doc.setObject(obj);
    file.write(doc.toJson());
    file.close();
    return 1;
}
bool Project::load_samples(QVector<QAction*>& vec_sample_sheets)
{
    //Открываем файл для считывания
    file.setFileName(path_sample);
    if (!file_open(1)) {
        return 0;
    }
    QString sample_file_txt;
    sample_file_txt = file.readAll();
    QJsonDocument docum = QJsonDocument::fromJson(sample_file_txt.toUtf8());
    QJsonObject jsonObject = docum.object();
    QJsonArray jsonArray = jsonObject["sample_sheet"].toArray();
    qDebug() << jsonArray.size();
    //Проходим по всем шаблонам и записываем данные в vec_sample_sheets
    for (int j = 0; j < jsonArray.size(); j++) {
        QJsonValue value = jsonArray[j];
        QAction* one_sample = new QAction;
        one_sample->setText(value["length"].toString() + " x " + value["width"].toString());
        vec_sample_sheets.push_back(one_sample);
    }
    return 1;
}
