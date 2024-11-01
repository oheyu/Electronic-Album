#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ipedit->setEchoMode(QLineEdit::Normal);
    QString ip_mask = "000.000.000.000;_";
    ui->ipedit->setInputMask(ip_mask);

    ui->maskedit->setEchoMode(QLineEdit::Normal);
    QString mac_mask = "HH:HH:HH:HH;_";
    ui->maskedit->setInputMask(mac_mask);

    ui->emailedit->setEchoMode(QLineEdit::Normal);
    //设置正则表达式过滤  secondtonone23@163.com
    QRegExp regx("[a-zA-Z0-9_-]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]+");

    QValidator *validator = new QRegExpValidator(regx, ui->emailedit );
    ui->emailedit->setValidator(validator);

    ui->passwdedit->setEchoMode(QLineEdit::Password);

}

MainWindow::~MainWindow()
{
    delete ui;
}
