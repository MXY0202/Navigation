#ifndef SINGLE_H
#define SINGLE_H

#include <QDialog>

namespace Ui {
class Single;
}

class Single : public QDialog
{
    Q_OBJECT

public:
    explicit Single(QWidget *parent = nullptr);
    ~Single();

private slots:
    void on_pointEdit_textChanged(const QString &arg1);

    void on_quitBtn_clicked();

    void on_startBtn_clicked();

private:
    Ui::Single *ui;
    QString endPoint;//终点
};

#endif // SINGLE_H
