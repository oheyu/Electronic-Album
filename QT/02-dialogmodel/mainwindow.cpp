#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    auto w = new QDialog(this);
//    w->show();

//    QDialog w(this);
//    w.exec();

//    auto w = new QDialog(this);
//    w->setModal(true);
//    w->show();

//    auto s = new QDialog(this);
//    s->setModal(true);

//    s->setWindowFlag(Qt::WindowStaysOnTopHint);
//    s->show();

//    QDialog w(this);
//    w.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
