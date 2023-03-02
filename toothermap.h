#ifndef TOOTHERMAP_H
#define TOOTHERMAP_H

#include <QDialog>

namespace Ui {
class ToOtherMap;
}

class ToOtherMap : public QDialog
{
    Q_OBJECT

public:
    explicit ToOtherMap(QWidget *parent = nullptr);
    ~ToOtherMap();

private slots:
    void on_shoolBusBtn_clicked();

    void on_busBtn_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::ToOtherMap *ui;
};

#endif // TOOTHERMAP_H
