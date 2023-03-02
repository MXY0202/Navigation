#ifndef DIALOGBUI_H
#define DIALOGBUI_H

#include <QDialog>

#include <QDialog>
#include <QPainter>
#include<QDebug>
#include<QMenu>
#include<QString>

namespace Ui {
class dialogBui;
}

class dialogBui : public QDialog
{
    Q_OBJECT

public:
    explicit dialogBui(QWidget *parent = 0);
    ~dialogBui();

private slots:
    void on_searchBtn_clicked();

    void on_goBtn_clicked();

private:
    Ui::dialogBui *ui;
};

#endif // DIALOGBUI_H

