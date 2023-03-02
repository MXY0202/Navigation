#ifndef DIALOGDINBEN_H
#define DIALOGDINBEN_H

#include <QDialog>
#include <QDialog>
#include<QMenu>
#include<QDebug>
namespace Ui {
class DialogDinBen;
}

class DialogDinBen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDinBen(QWidget *parent = 0);
    ~DialogDinBen();

private:
    Ui::DialogDinBen *ui;
};

#endif // DIALOGDINBEN_H


