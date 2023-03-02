#ifndef DIALOGDINSON_H
#define DIALOGDINSON_H

#include <QDialog>
#include <QDialog>
#include <QPainter>
#include<QDebug>
#include<QMenu>
namespace Ui {
class dialogdinSon;
}

class dialogdinSon : public QDialog
{
    Q_OBJECT

public:
    explicit dialogdinSon(QWidget *parent = 0);
    ~dialogdinSon();

private:
    Ui::dialogdinSon *ui;
};

#endif // DIALOGDINSON_H
