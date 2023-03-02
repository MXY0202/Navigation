#ifndef DIALOGGUI_H
#define DIALOGGUI_H

#include <QDialog>
#include<QDebug>
#include<QMenu>

namespace Ui {
class DialogGui;
}

class DialogGui : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGui(QWidget *parent = 0);
    ~DialogGui();

private:
    Ui::DialogGui *ui;
};

#endif // DIALOGGUI_H
