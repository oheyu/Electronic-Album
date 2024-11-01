#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->textEdit->setAcceptDrops(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //判断是否包含url
    if(event->mimeData()->hasUrls()){
        //接收动作
        event->acceptProposedAction();
    }else{
        //放弃事件
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent * event)
{

    const QMimeData * mimeData = event->mimeData();
    //判断是否包含url
    if(mimeData->hasUrls()){
        QList<QUrl> urlList = mimeData->urls();
        //将第一个匹配为本地文件路径
        QString filename = urlList[0].toLocalFile();
        if(!filename.isEmpty()){
            QTextCodec *codec=QTextCodec::codecForName("UTF-8");
            QFile file(filename);
            //打开文件失败
            if(!file.open(QIODevice::ReadOnly)){
                return;
            }
            QTextCodec::setCodecForLocale(codec);
            //打开成功
            QTextStream in(&file);
            //qDebug()<< "in readall is " << in.readAll() << endl;
            ui->textEdit->setText(in.readAll());
        }

    }else{
        event->ignore();
    }
}
