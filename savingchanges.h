#ifndef SAVINGCHANGES_H
#define SAVINGCHANGES_H

#include <QDialog>

namespace Ui {
class SavingChanges;
}

class SavingChanges : public QDialog {
    Q_OBJECT

public:
    explicit SavingChanges(QWidget* parent = nullptr);
    ~SavingChanges();
    int exec_flag();
private slots:
    void slot_yes();
    void slot_no();
    void slot_cancel();

private:
    Ui::SavingChanges* ui;
    int flag;
};

#endif // SAVINGCHANGES_H
