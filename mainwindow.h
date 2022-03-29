#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "add_ss.h"
#include "form.h"
#include "projectrect.h"
#include <QFrame>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct ComboFormInfo {
    QString f_name;
    QPoint f_top;
    int f_widht;
    int f_lenght;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
signals:
    void sig_check_complet(); // Запускает проверку на необходимость добавления фрейма.
    void sig_error(QString error_message); // Для вывода сообщения об ошибке.

private:
    void add_input_field(); // Добавление фрейма с полями для ввода данных.
    void create_sample_sheet(); // Создание шаблонов листов.
    void paint_list_sheet(int w, int h); // Отрисовка листа.
    void setstyle_list_vec_text_rects(QGraphicsTextItem& text_rect, QGraphicsRectItem* rect);
    void add_stock_in_vec(ProjectRect cur_stock); // Добавление заготовки в вектор с сортировкой по возрастанию.
    void clear_scene();
    void clear_all_data();
    void sort_vec_form_info(bool sort_index);
    bool algoritm_search_comb();
    bool algoritm_cutting(); // Рекурсивный алгоритм.
    bool check_on_dimension(int stok_w, int stok_l);

private slots:
    void slot_del_input_field(); // Удаление фрейма по нажатию кнопки с крестиком.
    void slot_edit_finished(); // Проверка на заполненость полей данных. Требуется ли создать новый фрейм?
    void slot_add_sample_sheet(); // Добавление нового шаблона в меню-бар.
    void slot_read_size_list_fsh(); // Получение данных о выбраном шаблоне в меню-баре.
    void slot_run(); // При нажатии "Собрать" выполняется подготовка данных и вызывается сам алгоритм.
    void slot_error(QString error_message); // Обработчик ошибок. Выводит текст сообщения в статус-бар.
    void slot_paint_solution(const QModelIndex& index); // Отрисовка всех ректов на грф. сцене.

private:
    QVector<ProjectRect> vec_stok;
    QVector<QAction*> vec_list_ss;
    QVector<QString> vec_sheet_list_bd;
    QVector<QGraphicsRectItem*> vec_rects;
    QVector<QGraphicsTextItem*> vec_text_rects;
    QVector<FormInfo> vec_form_info;
    QVector<ProjectRect> vec_form;
    QVector<QFrame*> vec_frame;
    QVector<int> vfii;
    QVector<ComboFormInfo> vec_comb_form;
    QVector<QVector<ComboFormInfo>> vec_solution;
    QGraphicsScene* scene = new QGraphicsScene;
    QGraphicsRectItem* sample_sheet = new QGraphicsRectItem;
    QSize currnet_sheet;
    QString error_code;
    QLabel* message_for_client = new QLabel;
    QStringListModel* model;
    const size_t increase = 1;
    Ui::MainWindow* ui;
};

bool next_group_variant(QVector<bool>& group_complete);
#endif // MAINWINDOW_H
