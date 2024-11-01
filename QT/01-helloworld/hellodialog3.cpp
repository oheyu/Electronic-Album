#include "hellodialog3.h"
#include "ui_hellodialog3.h"

HelloDialog3::HelloDialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelloDialog3)
{
    ui->setupUi(this);
}

HelloDialog3::~HelloDialog3()
{
    delete ui;
}
