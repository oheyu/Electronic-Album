#include "login.h"
#include "ui_login.h"
#include "register.h"
using namespace std;
Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_2_clicked()
{
    this->close();
    _register->show();
}


void Login::initSignals(){
    _register = make_shared<Register>();
    _register->set_login(shared_from_this());
}
