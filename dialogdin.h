#ifndef DIALOGDIN_H
#define DIALOGDIN_H

#include <QDialog>
#include <QPainter>
#include<QDebug>
#include<QMenu>
#include"dialogdinson.h"
namespace Ui {
class DialogDin;
}

class DialogDin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDin(QWidget *parent = 0);
    ~DialogDin();
private:
       void paintEvent(QPaintEvent *);

private:
    Ui::DialogDin *ui;
    dialogdinSon *dialogdson;
};

#endif // DIALOGDIN_H

