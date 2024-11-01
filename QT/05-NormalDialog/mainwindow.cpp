#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QMessageBox>
#include <QProgressDialog>
#include <QErrorMessage>
#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),_count(0),_progressDialog(nullptr)
{
    ui->setupUi(this);
    _err = new QErrorMessage();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _err;
}

void MainWindow::on_pushButton_clicked()
{
//    QColorDialog colorDlg(Qt::blue, this);
//    colorDlg.setOption(QColorDialog::ShowAlphaChannel);
//    colorDlg.exec();
//    QColor color = colorDlg.currentColor();
//    qDebug() << "color is " << color;

   QColor color = QColorDialog::getColor(Qt::blue, this,tr("选择颜色"), QColorDialog::ShowAlphaChannel );
    qDebug() << "color is " << color;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = QDir::currentPath();
    QString title = tr("文件对话框");
    QString filter = tr("文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)");
    QString aFileName=QFileDialog::getOpenFileName(this,title,path,filter);

    qDebug() << aFileName << endl;
}

void MainWindow::on_pushButton_3_clicked()
{
    bool ok = false;
    auto text = QInputDialog::getText(this, tr("文字输入对话框"), tr("请输入用户的姓名"), QLineEdit::Normal, tr("admin"), &ok);
    if(ok){
        qDebug() << text << endl;
    }


}

void MainWindow::on_pushButton_4_clicked()
{
     bool ok = false;
    auto intdata = QInputDialog::getInt(this,tr("数字输入对话框"),tr("请输入数字"),200,-200,400,10,&ok);
    if(ok){
        qDebug() << intdata << endl;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    bool ok = false;
    auto floatdata = QInputDialog::getDouble(this,tr("浮点数输入对话框"),tr("输入浮点数"),0.1,-1,1,2,&ok);
    if(ok){
        qDebug() << floatdata << endl;
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QStringList items;
    items << tr("条目1") << tr("条目2");
    bool ok = false;
    auto itemData = QInputDialog::getItem(this,tr("条目输入对话框"),tr("输入或选择条目"),items,0,true, &ok);
    if(ok){
        qDebug() << "item is " << itemData << endl;
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    auto ret = QMessageBox::question(this,tr("提问对话框"),tr("你是单身吗"),QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes || ret == QMessageBox::No){
        qDebug() << "ret is " << ret << endl;
    }

    auto ret2 = QMessageBox::information(this,tr("通知对话框"),tr("你好单身狗"),QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok){
        qDebug() << "ret2 is " << ret2 << endl;
    }

    auto ret3 = QMessageBox::warning(this,tr("警告对话框"),tr("你最好找个地方发泄一下"),QMessageBox::Ok);
    if(ret3 == QMessageBox::Ok){
        qDebug() << "ret3 is " << ret3 << endl;
    }

    auto ret4 = QMessageBox::critical(this,tr("关键提示对话框"), tr("我梦寐以求是真爱和自由"),QMessageBox::Ok);
    if(ret4 == QMessageBox::Ok){
        qDebug() << "ret4 is " << ret4 << endl;
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    // 进度提示框一闪而逝，不是逻辑问题，是5000量级太小了
//    QProgressDialog progressDialog(tr("正在复制"),tr("取消复制"),0,5000,this);
//    progressDialog.setWindowTitle(tr("文件复制进度对话框"));
//    progressDialog.setWindowModality(Qt::ApplicationModal);
//    progressDialog.show();

//    for(int i = 0; i < 5000; i++){
//        progressDialog.setValue(i);
//        QApplication::processEvents();
//        if(progressDialog.wasCanceled()){
//            break;
//        }
//    }
//    progressDialog.setValue(5000);

    //改用定时器
    _progressDialog = new QProgressDialog(tr("正在复制"),tr("取消复制"),0,5000,this);
    _progressDialog->setWindowTitle(tr("文件复制进度对话框"));
    _progressDialog->setWindowModality(Qt::ApplicationModal);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::on_updateProgressDialog);
    connect(_progressDialog, &QProgressDialog::canceled, this, &MainWindow::on_cancelProgressDialog);
    _timer->start(2);
    qDebug("复制结束");
}

void MainWindow::on_updateProgressDialog()
{
    _count++;
    if(_count > 5000){
        _timer->stop();
        delete  _timer;
        _timer = nullptr;
        delete _progressDialog;
        _progressDialog = nullptr;
        _count = 0;
        return;
    }

    _progressDialog->setValue(_count);
}

void MainWindow::on_cancelProgressDialog(){
    _timer->stop();
    delete  _timer;
    _timer = nullptr;
    delete _progressDialog;
    _progressDialog = nullptr;
    _count = 0;
    return;
}

void MainWindow::on_pushButton_9_clicked()
{
    _err->setWindowTitle(tr("错误提示对话框"));
    _err->showMessage(tr("你犯了个错误"));
}

void MainWindow::on_pushButton_10_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("全城热恋"));
    QWizardPage* page1 = new QWizardPage();
    page1->setTitle(tr("婚恋介绍引导程序"));
    auto label1 = new QLabel();
    label1->setText(tr("该程序帮助您找到人生伴侣"));
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label1);
    page1->setLayout(layout);
    wizard.addPage(page1);
    QWizardPage* page2 = new QWizardPage();
    page2->setTitle("选择心动类型");

    QButtonGroup *group = new QButtonGroup(page2);
    QRadioButton * btn1 = new QRadioButton();
    btn1->setText("白富美");
    group->addButton(btn1);
    QRadioButton * btn2 = new QRadioButton();
    btn2->setText("萝莉");
    group->addButton(btn2);
    QRadioButton * btn3 = new QRadioButton();
    btn3->setText("御姐");
    group->addButton(btn3);
    QRadioButton * btn4 = new QRadioButton();
    btn4->setText("小家碧玉");
    group->addButton(btn4);
    QRadioButton * btn5 = new QRadioButton();
    btn5->setText("女汉子");
    group->addButton(btn5);

    QRadioButton * btn6 = new QRadioButton();
    btn6->setText("成年人不做选择，全选!");
    group->addButton(btn6);
    QVBoxLayout *vboxLayout2 = new QVBoxLayout();
    for(int i = 0; i < group->buttons().size(); i++){
        vboxLayout2->addWidget(group->buttons()[i]);
    }

    page2->setLayout(vboxLayout2);
    wizard.addPage(page2);

    QWizardPage* page3 = new QWizardPage();
    page3->setTitle(tr("你的缘分即将到来"));
    auto label3 = new QLabel();
    label3->setText(tr("感谢您的参与，接下来的一个月会遇到对的人"));
    QVBoxLayout *layout3 = new QVBoxLayout();
    layout3->addWidget(label3);
    page3->setLayout(layout3);
    wizard.addPage(page3);


    wizard.show();
    wizard.exec();




}
