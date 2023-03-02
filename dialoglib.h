#ifndef DIALOGLIB_H
#define DIALOGLIB_H

#include <QDialog>
#include<QMenu>
#include<QDebug>
namespace Ui {
class DialogLib;
}

class DialogLib : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLib(QWidget *parent = 0);
    ~DialogLib();

private slots:
    //void on_floor5Btn_clicked();

private:
    Ui::DialogLib *ui;
};

#endif // DIALOGLIB_H
