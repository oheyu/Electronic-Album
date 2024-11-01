#include "myaction.h"
#include <QSplitter>
#include <QLabel>
#include <QSplitter>

MyAction::MyAction(QObject *parent):QWidgetAction(parent)
{
    //创建行编辑器
    lineEdit = new QLineEdit();
    //链接信号和槽，触发回车信号和发送文本的槽函数关联
    connect(lineEdit, &QLineEdit::returnPressed,this,&MyAction::sendText);
}

QWidget *MyAction::createWidget(QWidget *parent)
{
    //parent不继承QMenu 并且不继承QToolBar
    if(!(parent->inherits("QMenu")) &&  !(parent->inherits("QToolBar"))){
        return 0;
    }

    QSplitter * spliter = new QSplitter(parent);
    QLabel * label = new QLabel;
    label->setText(tr("插入文本"));
    spliter->addWidget(label);
    spliter->addWidget(lineEdit);
    return spliter;
}

void MyAction::sendText()
{
    emit getText(lineEdit->text());
    lineEdit->clear();
}
