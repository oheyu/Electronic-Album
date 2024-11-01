#include "childdialog.h"
#include "ui_childdialog.h"
#include <QDebug>
ChildDialog::ChildDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChildDialog),_parent(parent)
{
    ui->setupUi(this);
    connect(ui->showMainWindow, &QPushButton::clicked, this, &ChildDialog::showMainWindow);
}

ChildDialog::~ChildDialog()
{
    delete ui;
}

void ChildDialog::showMainWindow()
{
    qDebug() << "show main window" << endl;
    //_parent->show();
    this->hide();
    //可以再次发送信号通知主窗口显示
    emit showMainSig();
}
