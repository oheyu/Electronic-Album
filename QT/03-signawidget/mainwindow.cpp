#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "childdialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _child_dialog = new ChildDialog(this);
    //qt4 风格
    //connect(ui->showChildButton, SIGNAL(clicked(bool)), this, SLOT(showChildDialog()));

    //qt4 风格的Slot和Signal 只是宏转换，字符串定义不能检测编译错误
   // connect(ui->showChildButton, SIGNAL(clicked(bool)), this, SLOT(showChildDialog(1,2,3)));

    //推荐qt5 风格
    connect(ui->showChildButton, &QPushButton::clicked, this, &MainWindow::showChildDialog);

    connect(_child_dialog, &ChildDialog::showMainSig, this, &MainWindow::showMainDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(_child_dialog){
        delete  _child_dialog;
        _child_dialog = nullptr;
    }
}

void MainWindow::showChildDialog()
{
    qDebug() << "show child dialog " << endl;
//    auto childDialog = new ChildDialog(this);
//    childDialog->show();
    _child_dialog->show();
    this->hide();
}

void MainWindow::showMainDialog()
{
    this->show();
    _child_dialog->hide();
}
