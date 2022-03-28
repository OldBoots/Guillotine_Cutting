#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QInputDialog>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "form.h"
#include "add_ss.h"
#include "projectrect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sig_check_complet();                   // Запускает проверку на необходимость добавления фрейма.
    void sig_error(QString error_message);      // Для вывода сообщения об ошибке.

private:
    void add_input_field();                     // Добавление фрейма с полями для ввода данных.
    void create_sample_sheet();                 // Создание шаблонов листов.
    void paint_list_sheet(int w, int h);        // Отрисовка листа.
    void paint_list_vec_rects();                    // Отрисовка всех ректов на грф. сцене.
    void setstyle_list_vec_text_rects(QGraphicsTextItem &text_rect, QGraphicsRectItem *rect);
    int algoritm_cutting();                   // Рекурсивный алгоритм.
    void add_stock_in_vec(ProjectRect cur_stock);     // Добавление заготовки в вектор с сортировкой по возрастанию.
    void paint_vec_form();
    void clear_scene();
    void clear_all_data();
    void sort_vec_form_info(bool sort_index);
    bool check_on_dimension(int stok_w, int stok_l);

private slots:
    void slot_del_input_field();                // Удаление фрейма по нажатию кнопки с крестиком.
    void slot_edit_finished();                  // Проверка на заполненость полей данных. Требуется ли создать новый фрейм?
    void slot_add_sample_sheet();               // Добавление нового шаблона в меню-бар.
    void slot_read_size_list_fsh();             // Получение данных о выбраном шаблоне в меню-баре.
    void slot_run();                            // При нажатии "Собрать" выполняется подготовка данных и вызывается сам алгоритм.
    void slot_error(QString error_message);     // Обработчик ошибок. Выводит текст сообщения в статус-бар.

private:
    QVector<ProjectRect> vec_stok;
    QVector<QAction *> vec_list_ss;
    QVector<QString> vec_sheet_list_bd;
    QVector<QGraphicsRectItem *> vec_rects;
    QVector<QGraphicsTextItem *> vec_text_rects;
    QVector<FormInfo> vec_form_info;
    QVector<ProjectRect> vec_form;
    QVector<QFrame *> vec_frame;
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsRectItem *sample_sheet = new QGraphicsRectItem;
    QSize currnet_sheet;
    QString error_code;
    QLabel *message_for_client = new QLabel;
    const size_t increase = 1;
    QVector<int> vfii;
    Ui::MainWindow *ui;
};

bool next_group_variant(QVector <bool> &group_complete);
#endif // MAINWINDOW_H
