#ifndef MULTIPOINTS_H
#define MULTIPOINTS_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QStack>
#include <QGridLayout>
namespace Ui {
class MultiPoints;
}

class MultiPoints : public QDialog
{
    Q_OBJECT

public:
    explicit MultiPoints(QWidget *parent = nullptr);
    ~MultiPoints();
    void addPoints(int num);

private slots:


    void on_confirmBtn_clicked();

    void on_quitBtn_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_endEdit_returnPressed();

private:
    Ui::MultiPoints *ui;
    QStack<QLabel *> myLabel;
    QStack<QLineEdit *> buildingEdit;
    QGridLayout* grad;
    QString endPoint;
    int multiNum;//存储LineEdit存放的途径多点数目
};

#endif // MULTIPOINTS_H
