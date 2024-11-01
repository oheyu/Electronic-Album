#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction* action_print = new QAction(tr("打印"),this);
    QAction* action_printview = new QAction(tr("打印预览"),this);
    QAction* action_pdf = new QAction(tr("生成pdf"),this);
    connect(action_print, &QAction::triggered, this, &MainWindow::DoPrint);
    connect(action_printview, &QAction::triggered, this, &MainWindow::DoPrintPreview);
    connect(action_pdf, &QAction::triggered, this, &MainWindow::CreatePdf);
    ui->mainToolBar->addAction(action_print);
    ui->mainToolBar->addAction(action_printview);
    ui->mainToolBar->addAction(action_pdf);
    this->resize(1000,800);
    ui->textEdit->resize(960,700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DoPrint()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    //判断编辑区域是否有选中
    if(ui->textEdit->textCursor().hasSelection()){
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }

    //如果对话框中点击了确定按钮，则打印数据
    if(dlg.exec() == QDialog::Accepted){
        ui->textEdit->print(&printer);
    }
}

void MainWindow::DoPrintPreview()
{
    QPrinter printer;
    //创建打印预览界面
    QPrintPreviewDialog preview_dlg(&printer, this);

    //绑定该预览对话框和mainwindow的打印预览关系
    connect(&preview_dlg, &QPrintPreviewDialog::paintRequested, this, &MainWindow::PrintPreview);
    //模态执行打印预览对话框
    preview_dlg.exec();
}

void MainWindow::PrintPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}

void MainWindow::CreatePdf()
{
    auto filename = QFileDialog::getSaveFileName(this, tr("导出PDF"),"","*.pdf");
    //判断文件是否存在
    if(!filename.isEmpty()){
        //文件没后缀
        if(QFileInfo(filename).suffix().isEmpty()){
            filename.append(".pdf");
        }

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        ui->textEdit->print(&printer);
    }
}
