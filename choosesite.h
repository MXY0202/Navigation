#ifndef CHOOSESITE_H
#define CHOOSESITE_H

#include <QDialog>

namespace Ui {
class ChooseSite;
}

class ChooseSite : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseSite(QWidget *parent = nullptr);
    ~ChooseSite();

private slots:
    void on_lineEdit_editingFinished();

    void on_confirmBtn_clicked();

private:
    Ui::ChooseSite *ui;
    QString site;
};

#endif // CHOOSESITE_H
