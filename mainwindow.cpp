#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choosesite.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ChooseSite * chooseSite = new ChooseSite;
    ui->setupUi(this);
    QPalette pal =this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/pictures/badge.jpg")));
    setPalette(pal);
    ui->startBtn->setText("进入");
    connect(ui->startBtn, &QPushButton::clicked, chooseSite, &ChooseSite::show);
    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::close);
    ui->quitBtn->setText("退出");
    connect(ui->quitBtn, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

