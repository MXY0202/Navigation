#ifndef DIALOGLIBBEN_H
#define DIALOGLIBBEN_H


#include <QDialog>
#include<QMenu>
#include<QDebug>

namespace Ui {
class DialogLibBen;
}

class DialogLibBen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLibBen(QWidget *parent = 0);
    ~DialogLibBen();

private:
    Ui::DialogLibBen *ui;
};

#endif // DIALOGLIBBEN_H

