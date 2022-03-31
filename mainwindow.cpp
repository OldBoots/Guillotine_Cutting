#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    add_input_field();
    create_sample_sheet();
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setScene(scene);
    message_for_client->setStyleSheet("QLabel {font-size: 14pt; color : red;}");
    ui->statusbar->addWidget(message_for_client);
    paint_list_sheet(680, 490);
    scene->addItem(sample_sheet);

    model = new QStringListModel;
    load_project = new QAction;
    load_project->setText("Открыть проект");
    save_project = new QAction;
    save_project->setText("Сохранить");
    save_as_project = new QAction;
    save_as_project->setText("Сохранить как..");
    create_project = new QAction;
    create_project->setText("Создать проект");
    ui->listView->setModel(model);
    ui->listView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->file->addAction(create_project);
    ui->file->addAction(load_project);
    ui->file->addAction(save_project);
    ui->file->addAction(save_as_project);
    connect(load_project, SIGNAL(triggered()), SLOT(slot_load_project()));
    connect(save_project, SIGNAL(triggered()), SLOT(slot_save_project()));
    connect(save_as_project, SIGNAL(triggered()), SLOT(slot_save_as_project()));
    connect(create_project, SIGNAL(triggered()), SLOT(slot_create_project()));

    connect(ui->listView, SIGNAL(clicked(const QModelIndex)), this, SLOT(slot_paint_solution(const QModelIndex)));
    connect(this, SIGNAL(sig_check_complet()), this, SLOT(slot_edit_finished()));
    connect(vec_list_ss[0], SIGNAL(triggered()), SLOT(slot_add_sample_sheet()));
    connect(vec_list_ss[1], SIGNAL(triggered()), SLOT(slot_read_size_list_fsh()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_run()));
    connect(this, SIGNAL(sig_error(QString)), this, SLOT(slot_error(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_stock_in_vec(ProjectRect cur_stock)
{
    vec_stok << cur_stock;
    for (int i = vec_stok.size() - 1; i > 0; i--) {
        if (vec_stok[i].width() < vec_stok[i - 1].width()) {
            qSwap(vec_stok[i], vec_stok[i - 1]);
        } else if (vec_stok[i].width() == vec_stok[i - 1].width() && vec_stok[i].length() < vec_stok[i - 1].length()) {
            qSwap(vec_stok[i], vec_stok[i - 1]);
        } else {
            break;
        }
    }
}

bool MainWindow::algoritm_cutting()
{
    ProjectRect current_stock;
    bool flag_next_form = true;
    bool flag_no_valid_stok = true;
    int count_form = vec_form.size();
    // Алгоритм будет выполняться пока не кончатся мерные обрезки или формы
    while (count_form != 0 && !vec_stok.isEmpty()) {
        flag_next_form = true;
        // Проходим остатки
        for (int i = 0; i < vec_stok.size() && flag_next_form; i++) {
            flag_no_valid_stok = true;
            // Пытаемся поместить форму
            for (int j = 0; j < vec_form.size() && flag_next_form; j++) {
                // Если форма не добавленна, влазит по l и w, то помещаем ее
                if (!vec_form[j].added() && vec_form[j].width() <= vec_stok[i].width() && vec_form[j].length() <= vec_stok[i].length()) {
                    current_stock = vec_stok[i];
                    vec_stok.remove(i);
                    vec_form[j].set_top(current_stock.top());
                    vec_form[j].set_added(true);
                    count_form--;
                    flag_next_form = false;
                    flag_no_valid_stok = false;
                    // Добавляем Два получившихся остатка, если они мерные
                    if (current_stock.width() > vec_form[j].width() && check_on_dimension(current_stock.width() - vec_form[j].width(), current_stock.length())) {
                        add_stock_in_vec(ProjectRect(current_stock.x() + vec_form[j].width(),
                            current_stock.y(),
                            current_stock.width() - vec_form[j].width(),
                            current_stock.length()));
                    }
                    if (current_stock.length() > vec_form[j].length() && check_on_dimension(vec_form[j].width(), current_stock.length() - vec_form[j].length())) {
                        add_stock_in_vec(ProjectRect(current_stock.x(),
                            current_stock.y() + vec_form[j].length(),
                            vec_form[j].width(),
                            current_stock.length() - vec_form[j].length()));
                    }
                }
            }
            if (flag_no_valid_stok) {
                vec_stok.remove(i);
                i--;
            }
        }
    }
    // Проверяем получилось ли разместить все формы
    bool complete = true;
    for (int i = 0; i < vec_form.size(); i++) {
        if (!vec_form[i].added()) {
            complete = false;
        }
    }
    return complete;
}

void MainWindow::slot_error(QString error_massage)
{
    QStringList message = error_massage.split("_");
    error_code = message[1];
    message_for_client->setText(message[0]);
}

void MainWindow::clear_all_data()
{
    clear_scene();
    if (!message_for_client->text().isEmpty()) {
        message_for_client->clear();
        message_for_client->update();
        error_code.clear();
    }
    if (!vec_form_info.isEmpty()) {
        vec_form_info.clear();
    }
    if (!vec_form.isEmpty()) {
        vec_form.clear();
    }
    if (!vec_stok.isEmpty()) {
        vec_stok.clear();
    }
    if (!vec_rects.isEmpty()) {
        vec_rects.clear();
    }
    if (!vec_text_rects.isEmpty()) {
        vec_text_rects.clear();
    }
    if (!error_code.isEmpty()) {
        error_code.clear();
    }
    if (!vfii.isEmpty()) {
        vfii.clear();
    }
    if (!vec_solution.isEmpty()) {
        vec_solution.clear();
    }
}

void MainWindow::slot_run()
{
    QStringList list_solutions;
    // Обнуляем данные
    clear_all_data();
    int area_sheet, area_general = 0;
    area_sheet = currnet_sheet.width() * currnet_sheet.height();
    // Считываем данные с полей ввода
    for (int i = 0; i < vec_frame.size() - 1; i++) {
        FormInfo form(vec_frame[i]->findChild<QLineEdit*>("ln_name")->text(),
            vec_frame[i]->findChild<QLineEdit*>("ln_length")->text().toInt(),
            vec_frame[i]->findChild<QLineEdit*>("ln_width")->text().toInt(),
            vec_frame[i]->findChild<QLineEdit*>("ln_number")->text().toInt());
        if (vec_frame[i]->findChild<QLineEdit*>("ln_length")->text().isEmpty() || vec_frame[i]->findChild<QLineEdit*>("ln_width")->text().isEmpty() || vec_frame[i]->findChild<QLineEdit*>("ln_number")->text().isEmpty()) {
            emit sig_error("Ворма \"" + form.name() + "\" задана неверно._S1");
            return;
        }
        if ((currnet_sheet.width() < form.width() || currnet_sheet.height() < form.length())) {
            emit sig_error("Форма \"" + form.name() + "\" не входит на лист._S2");
            return;
        }
        area_general += form.width() * form.length() * form.numb();
        // Добавляем запись в вектор vec_form_info
        vec_form_info << form;
    }
    // Сортируем группы форм по убыванию
    sort_vec_form_info(false);
    if (area_sheet < area_general) {
        emit sig_error("Общая площадь форм больше площади листа._S3");
        return;
    }
    // Заполняем вектор форм
    for (int i = 0; i < vec_form_info.size(); i++) {
        for (int j = 0; j < vec_form_info[i].numb(); j++) {
            vec_form << ProjectRect(0, 0, vec_form_info[i].width(), vec_form_info[i].length(), vec_form_info[i].name(), false);
        }
    }
    //Определяем количество вариантов компоновки форм для выбора пользователем
    vec_stok << ProjectRect(0, 0, currnet_sheet.width(), currnet_sheet.height());
    if (algoritm_search_comb()) {
        for (int i = 0; i < vec_solution.size(); i++) {
            list_solutions << "Вариант " + QString::number(i + 1);
        }
    } else {
        emit sig_error("Не удалось разместить формы на листе._S4");
    }
    model->setStringList(list_solutions);
}

bool MainWindow::algoritm_search_comb()
{
    // Вектор вариантов поворотов групп
    QVector<bool> group_complete;
    group_complete.resize(vec_form_info.size(), 0);
    bool ngv = true;
    // Инициализируем вектор индексов групп форм
    for (int i = 0; i < vec_form_info.size(); i++) {
        vfii << i;
    }
    // Цикл перебора вариантов компановок
    while (ngv) {
        // Алгоритм разреза
        if (algoritm_cutting()) {
            for (int i = 0; i < vec_form.size(); i++) {
                vec_comb_form.push_back(ProjectRect(vec_form[i].top(), vec_form[i].width(), vec_form[i].length(), vec_form[i].name()));
            }
            vec_solution << vec_comb_form;
        }
        // Отчищаем вектора данных перед итерацией
        vec_comb_form.clear();
        vec_stok.clear();
        vec_form.clear();
        // Выбераем следующую комбинацию поворотов
        ngv = next_group_variant(group_complete);
        // Первый остаток
        vec_stok << ProjectRect(0, 0, currnet_sheet.width(), currnet_sheet.height());
        // Задаем повороты групп
        for (int i = 0; i < vec_form_info.size(); i++) {
            vec_form_info[i].set_turn(group_complete[i]);
        }
        // Сортируем группы форм
        sort_vec_form_info(true);
        // Заполняем вектор форм данными о поворотах
        for (int i = 0; i < vec_form_info.size(); i++) {
            for (int j = 0; j < vec_form_info[vfii[i]].numb(); j++) {
                vec_form << ProjectRect(0, 0, vec_form_info[vfii[i]].width(), vec_form_info[vfii[i]].length(), vec_form_info[vfii[i]].name(), false);
                vec_form[vec_form.size() - 1].set_turn(vec_form_info[vfii[i]].turn());
            }
        }
    }
    // Получено ли решение? Если вектор НЕ пустой, то решение получено
    return !vec_solution.isEmpty();
}

void MainWindow::sort_vec_form_info(bool sort_index)
{
    for (int i = 0; i < vec_form_info.size() - 1; i++) {
        for (int j = 0; j < vec_form_info.size() - 1 - i; j++) {
            if (sort_index) {
                if (vec_form_info[vfii[j]].length() < vec_form_info[vfii[j + 1]].length()) {
                    qSwap(vfii[j], vfii[j + 1]);
                } else if (vec_form_info[vfii[j]].length() == vec_form_info[vfii[j + 1]].length() && vec_form_info[vfii[j]].width() < vec_form_info[vfii[j + 1]].width()) {
                    qSwap(vfii[j], vfii[+1]);
                }
            } else {
                if (vec_form_info[j].length() < vec_form_info[j + 1].length()) {
                    qSwap(vec_form_info[j], vec_form_info[j + 1]);
                } else if (vec_form_info[j].length() == vec_form_info[j + 1].length() && vec_form_info[j].width() < vec_form_info[j + 1].width()) {
                    qSwap(vec_form_info[j], vec_form_info[j + 1]);
                }
            }
        }
    }
}

bool MainWindow::check_on_dimension(int stok_w, int stok_l)
{
    // Проверяем влазит ли хоть одна оставшаяся форма в этот обрезок
    for (int i = 0; i < vec_form.size(); i++) {
        if (!vec_form[i].added() && stok_w >= vec_form[i].width() && stok_l >= vec_form[i].length()) {
            return true;
        }
    }
    return false;
}

bool next_group_variant(QVector<bool>& group_complete)
{
    for (int i = group_complete.size() - 1; i >= 0;) {
        if (group_complete[i] == 0) {
            group_complete[i] = 1;
            break;
        } else {
            group_complete[i] = 0;
            i--;
        }
        if (i < 0) {
            return false;
        }
    }
    return true;
}

void MainWindow::slot_edit_finished()
{
    if (!vec_frame[vec_frame.size() - 1]->findChild<QLineEdit*>("ln_name")->text().isEmpty() && !vec_frame[vec_frame.size() - 1]->findChild<QLineEdit*>("ln_length")->text().isEmpty() && !vec_frame[vec_frame.size() - 1]->findChild<QLineEdit*>("ln_width")->text().isEmpty() && !vec_frame[vec_frame.size() - 1]->findChild<QLineEdit*>("ln_number")->text().isEmpty()) {
        add_input_field();
    }
}

void MainWindow::slot_del_input_field()
{
    clear_all_data();
    if (vec_frame.size() > 1) {
        int n_form = vec_frame.size();
        bool del_flg = false;
        for (int i = 0; i < n_form; i++) {
            if (vec_frame[i]->findChild<QPushButton*>("butt_del")->isChecked()) {
                ui->vertical_layout->removeWidget(vec_frame[i]);
                delete vec_frame[i];
                vec_frame.remove(i);
                ui->vertical_layout->update();
                n_form--;
                del_flg = true;
            }
            if (vec_frame.size() == i) {
                break;
            }
            if (del_flg) {
                vec_frame[i]->findChild<QLabel*>("lbl_index")->setText(QString::number(i + 1));
            }
        }
    } else {
        vec_frame[vec_frame.size() - 1]->findChild<QPushButton*>("butt_del")->setChecked(false);
    }
    if (vec_frame.size() == 1) {
        emit sig_check_complet();
    }
}

void MainWindow::add_input_field()
{
    vec_frame << new QFrame(this);
    QLabel* lbl_length = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLabel* lbl_width = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLabel* lbl_index = new QLabel(vec_frame[vec_frame.size() - 1]);
    lbl_index->setObjectName("lbl_index");
    QLabel* lbl_number = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLabel* lbl_name = new QLabel(vec_frame[vec_frame.size() - 1]);
    QLineEdit* ln_length = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_length->setObjectName("ln_length");
    QLineEdit* ln_width = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_width->setObjectName("ln_width");
    QLineEdit* ln_number = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_number->setObjectName("ln_number");
    QLineEdit* ln_name = new QLineEdit(vec_frame[vec_frame.size() - 1]);
    ln_name->setObjectName("ln_name");
    QPushButton* butt_del = new QPushButton(vec_frame[vec_frame.size() - 1]);
    butt_del->setObjectName("butt_del");

    vec_frame[vec_frame.size() - 1]->setFixedSize(300, 120);
    vec_frame[vec_frame.size() - 1]->setStyleSheet("QFrame { background-color: #B7CBD8 }");
    vec_frame[vec_frame.size() - 1]->setFrameShape(QFrame::StyledPanel);

    lbl_name->setText("Имя");
    lbl_name->setGeometry(190, 30, 30, 16);

    lbl_index->setText(QString::number(vec_frame.size()) + ".");
    QFont font;
    font.setPixelSize(16);
    lbl_index->setFont(font);
    lbl_index->setGeometry(2, 50, 20, 17);

    lbl_length->setText("Длина");
    lbl_length->setGeometry(50, 60, 41, 16);

    lbl_width->setText("Ширина");
    lbl_width->setGeometry(125, 60, 49, 16);

    lbl_number->setText("Кол-во");
    lbl_number->setGeometry(210, 60, 49, 16);

    ln_name->setGeometry(40, 30, 130, 22);
    connect(ln_name, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    ln_length->setGeometry(40, 80, 60, 22);
    ln_length->setValidator(new QIntValidator(0, 999, this));
    connect(ln_length, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    ln_width->setGeometry(120, 80, 60, 22);
    ln_width->setValidator(new QIntValidator(0, 999, this));
    connect(ln_width, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    ln_number->setGeometry(200, 80, 60, 22);
    ln_number->setValidator(new QIntValidator(0, 999, this));
    connect(ln_number, SIGNAL(editingFinished()), this, SLOT(slot_edit_finished()));

    butt_del->setCheckable(true);
    butt_del->setFlat(true);
    butt_del->setGeometry(270, 10, 21, 21);
    butt_del->setIcon(QIcon(QPixmap(":/close.png").scaled(21, 21)));

    connect(butt_del, SIGNAL(clicked()), this, SLOT(slot_del_input_field()));

    ui->vertical_layout->addWidget(vec_frame[vec_frame.size() - 1]);
}
void MainWindow::load_fill_frame()
{
    for (int i = 0; i < vec_form_info.size(); i++) {
        add_input_field();
        vec_frame[i]->findChild<QLineEdit*>("ln_name")->setText(vec_form_info[i].name());
        vec_frame[i]->findChild<QLineEdit*>("ln_length")->setText(QString::number(vec_form_info[i].length()));
        vec_frame[i]->findChild<QLineEdit*>("ln_width")->setText(QString::number(vec_form_info[i].width()));
        vec_frame[i]->findChild<QLineEdit*>("ln_number")->setText(QString::number(vec_form_info[i].numb()));
    }
    add_input_field();
}
void MainWindow::load_model_view()
{
    QStringList list_solutions;
    for (int i = 0; i < vec_solution.size(); i++) {
        list_solutions << "Вариант " + QString::number(i + 1);
    }
    model->setStringList(list_solutions);
}
void MainWindow::clear_scene()
{
    for (int i = 0; i < vec_rects.size(); i++) {
        scene->removeItem(vec_rects[i]);
        scene->removeItem(vec_text_rects[i]);
    }
    if (!vec_rects.isEmpty()) {
        vec_rects.clear();
    }
    if (!vec_text_rects.isEmpty()) {
        vec_text_rects.clear();
    }
    scene->update();
    ui->graphicsView->update();
}

void MainWindow::create_sample_sheet()
{
    QAction* plus = new QAction();
    QAction* a4 = new QAction();
    a4->setText("297 x 210");
    plus->setText("Добавить шаблон..");
    vec_list_ss.push_back(plus);
    vec_list_ss.push_back(a4);
    ui->menu->addAction(vec_list_ss[0]);
    ui->menu->addAction(vec_list_ss[1]);
    for (int i = 0; i < vec_sheet_list_bd.size(); i++) {
        QAction* sheet = new QAction();
        sheet->setText(vec_sheet_list_bd[i]);
        vec_list_ss.push_back(sheet);
        ui->menu->addAction(vec_list_ss[vec_list_ss.size() - 1]);
        connect(vec_list_ss[vec_list_ss.size() - 1], SIGNAL(triggered()), SLOT(slot_read_size_list_fsh()));
    }
}

void MainWindow::slot_add_sample_sheet()
{
    Add_ss* dialog = new Add_ss;
    dialog->setFixedSize(200, 100);
    dialog->setWindowTitle("Создание шаблона");
    QString we_he;
    if (dialog->exec()) {
        we_he = QString::number(dialog->h);
        we_he += " x " + QString::number(dialog->w);
    }
    QAction* sheet = new QAction();
    ui->menu->addAction(sheet);
    sheet->setText(we_he);
    vec_list_ss.push_back(sheet);
    connect(vec_list_ss[vec_list_ss.size() - 1], SIGNAL(triggered()), SLOT(slot_read_size_list_fsh()));
}

void MainWindow::paint_list_sheet(int w, int h)
{
    //    ui->graphicsView->update();
    sample_sheet->setRect(0, 0, w * increase, h * increase);
    currnet_sheet = QSize(w, h);
}

void MainWindow::slot_read_size_list_fsh()
{
    clear_scene();

    QObject* name = QObject::sender();
    QAction* sheet = qobject_cast<QAction*>(name);
    QStringList we_he = sheet->text().split(" x ");
    paint_list_sheet(we_he[0].toInt(), we_he[1].toInt());
}
void MainWindow::slot_save_as_project()
{
    proj_work.saveAs(vec_form_info, vec_solution);
}
void MainWindow::slot_create_project()
{
    clear_all_data();
    for (int i = vec_frame.size() - 1; i >= 0; i--) {
        ui->vertical_layout->removeWidget(vec_frame[i]);
        delete vec_frame[i];
        vec_frame.remove(i);
        ui->vertical_layout->update();
    }
    clear_scene();
    add_input_field();
    proj_work.path = QString();
    for (int i = model->rowCount() - 1; i >= 0; i--) {
        model->removeRow(i);
    }
}
void MainWindow::slot_save_project()
{
    proj_work.save(vec_form_info, vec_solution);
}
void MainWindow::slot_load_project()
{
    clear_all_data();
    for (int i = vec_frame.size() - 1; i >= 0; i--) {
        ui->vertical_layout->removeWidget(vec_frame[i]);
        delete vec_frame[i];
        vec_frame.remove(i);
        ui->vertical_layout->update();
    }
    clear_scene();
    for (int i = model->rowCount() - 1; i >= 0; i--) {
        model->removeRow(i);
    }
    proj_work.load(vec_form_info, vec_solution);
    load_fill_frame();
    load_model_view();
}

void MainWindow::setstyle_list_vec_text_rects(QGraphicsTextItem& text_rect, QGraphicsRectItem* rect)
{
    qreal x_rect, y_rect, w_rect, h_rect;
    QRectF getposrect;
    getposrect = rect->rect();
    getposrect.getRect(&x_rect, &y_rect, &w_rect, &h_rect);
    text_rect.setPos(x_rect + 1, y_rect + 1);
    text_rect.setTextWidth(w_rect);
    QFont font;
    font.setPixelSize((w_rect + h_rect) / 15);
    text_rect.setFont(font);
}

void MainWindow::slot_paint_solution(const QModelIndex& index)
{

    clear_scene();
    for (int i = 0; i < vec_solution[index.row()].size(); i++) {
        vec_rects << new QGraphicsRectItem(vec_solution[index.row()][i].x() * increase,
            vec_solution[index.row()][i].y() * increase,
            vec_solution[index.row()][i].width() * increase,
            vec_solution[index.row()][i].length() * increase);
        vec_text_rects << new QGraphicsTextItem(vec_solution[index.row()][i].name() + "\n" + QString::number(vec_solution[index.row()][i].width()) + "x" + QString::number(vec_solution[index.row()][i].length()));
    }
    for (int i = 0; i < vec_rects.size(); i++) {
        scene->addItem(vec_rects[i]);
        setstyle_list_vec_text_rects(*vec_text_rects[i], vec_rects[i]);
        scene->addItem(vec_text_rects[i]);
    }
}
