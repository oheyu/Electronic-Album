#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextFrame>
#include <QAction>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   QTextDocument *doc= ui->textEdit->document();
   QTextFrame* root_frame = doc->rootFrame();
   QTextFrameFormat format;
   format.setBorderBrush(Qt::blue);
   format.setBorder(3);
   root_frame->setFrameFormat(format);
   ui->textEdit->insertPlainText("hello world!\n");
   ui->textEdit->insertPlainText("Hello Qt\n");
   QTextFrameFormat  frameFormat;
   frameFormat.setBackground(Qt::lightGray);
   frameFormat.setMargin(10);
   frameFormat.setPadding(5);
   frameFormat.setBorder(2);
   frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dashed);
   QTextCursor cursor = ui->textEdit->textCursor();
   cursor.insertFrame(frameFormat);
   ui->textEdit->insertPlainText("inner text!\n");
   ui->textEdit->insertPlainText("Hello inner Text!\n");

   QAction * action_frame = new QAction("Frame",this);
   connect(action_frame, &QAction::triggered,this, &MainWindow::showTextFrame);
   ui->mainToolBar->addAction(action_frame);

   QAction* action_textBlock = new QAction(tr("文本块"),this);
   connect(action_textBlock, &QAction::triggered, this, &MainWindow::showTextBlock);
   ui->mainToolBar->addAction(action_textBlock);

   QAction* action_font = new QAction(tr("字体"), this);
   action_font->setCheckable(true);
   connect(action_font, &QAction::toggled, this, &MainWindow::setTextFont);
   ui->mainToolBar->addAction(action_font);

   QAction* action_textTable = new QAction(tr("表格"), this);
   QAction* action_textList = new QAction(tr("列表"), this);
   QAction* action_textImage = new QAction(tr("图片"), this);
   connect(action_textTable, &QAction::triggered,this, &MainWindow::insertTable);
   ui->mainToolBar->addAction(action_textTable);
   connect(action_textList, &QAction::triggered,this, &MainWindow::insertList);
   ui->mainToolBar->addAction(action_textList);
   connect(action_textImage, &QAction::triggered,this, &MainWindow::insertImage);
   ui->mainToolBar->addAction(action_textImage);

   QAction* action_textFind = new QAction(tr("查找"), this);
   connect(action_textFind, &QAction::triggered, this, &MainWindow::textFind);
   ui->mainToolBar->addAction(action_textFind);

   findDialog = new QDialog(this);
   lineEdit = new QLineEdit(findDialog);
   QPushButton * btn = new QPushButton(findDialog);
   btn->setText(tr("查找下一个"));
   connect(btn, &QPushButton::clicked, this, &MainWindow::findNext);
   QVBoxLayout* layout = new QVBoxLayout();
   layout->addWidget(lineEdit);
   layout->addWidget(btn);
   findDialog->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()
{
    auto doc = ui->textEdit->document();
    auto rootFrame = doc->rootFrame();
    for(auto iter = rootFrame->begin(); iter != rootFrame->end(); iter++){
        auto cur_frame = iter.currentFrame();
        auto cur_block = iter.currentBlock();
        if(cur_frame){
            qDebug() << "cur node is frame " ;
        } else if(cur_block.isValid()){
            qDebug() << "cur node is text block ,text is " << cur_block.text();
        }

    }
}

void MainWindow::showTextBlock()
{
    QTextDocument* document = ui->textEdit->document();
    QTextBlock block = document->firstBlock();
    for(int i = 0; i < document->blockCount(); i++){
        qDebug() << tr("文本块%1, 文本块首行行号%2, 长度%3, 内容%4").arg(i).arg(block.firstLineNumber()).arg(block.length())
                 << block.text();
        block = block.next();
    }
}

void MainWindow::setTextFont(bool checked)
{
    if(checked){
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignCenter);
        cursor.insertBlock(blockFormat);
        QTextCharFormat charFormat;
        charFormat.setBackground(Qt::lightGray);
        charFormat.setForeground(Qt::blue);
        charFormat.setFont(QFont(tr("宋体"),12,QFont::Bold,true));
        charFormat.setFontUnderline(true);
        cursor.setCharFormat(charFormat);
        cursor.insertText(tr("插入字体"));
    }else{
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignLeft);
        cursor.insertBlock(blockFormat);
        QTextCharFormat charFormat;
//        charFormat.setBackground(Qt::white);
//        charFormat.setForeground(Qt::black);
//        charFormat.setFont(QFont(tr("微软雅黑"),12,QFont::Normal, false));
//        charFormat.setFontUnderline(false);
        cursor.setCharFormat(charFormat);
        cursor.insertText(tr("微软雅黑字体"));
    }
}

void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;
    format.setCellSpacing(2);
    format.setCellPadding(10);
    cursor.insertTable(2,2,format);
}

void MainWindow::insertList(){
    QTextListFormat format;
    format.setStyle(QTextListFormat::ListDecimal);
    ui->textEdit->textCursor().insertList(format);
}

void MainWindow::insertImage(){
    QTextImageFormat format;
    format.setName(":/img/head.jpg");
    ui->textEdit->textCursor().insertImage(format);
}

void MainWindow::textFind(){
    findDialog->show();
}

void MainWindow::findNext(){
    QString string = lineEdit->text();
    bool isFind = ui->textEdit->find(string, QTextDocument::FindBackward);
    if(isFind){
        qDebug() << tr("行号:%1 列号:%2").arg(ui->textEdit->textCursor().blockNumber())
                    .arg(ui->textEdit->textCursor().columnNumber());
    }
}
