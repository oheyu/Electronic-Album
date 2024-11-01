#include "widget.h"
#include "ui_widget.h"
#include <QCursor>
#include <QPixmap>
#include <QDebug>
#include <QEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建光标对象
    QCursor cursor;
    //修改鼠标形状
    cursor.setShape(Qt::OpenHandCursor);
    //设置鼠标
    setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //如果是鼠标左键按下
    if(event->button() == Qt::LeftButton){
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
        offset = event->globalPos() - pos();

    }else if(event->button() == Qt::RightButton){
        QCursor cursor(QPixmap(":/res/mouse.png"));
        QApplication::setOverrideCursor(cursor);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //释放事件
    QApplication::restoreOverrideCursor();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        qDebug() << "event button is " << event->button() << endl;
        qDebug() << "window state is " << windowState() << endl;
        if(windowState() != Qt::WindowFullScreen){
            setWindowState(Qt::WindowFullScreen);
        }else{
            setWindowState(Qt::WindowNoState);
        }
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //移动过程中判断鼠标是左键点击并且移动，那么要用buttons，返回的是鼠标状态的集合
    if(event->buttons() & Qt::LeftButton){
        //获取窗口应当移动到的位置
        QPoint windowpos = event->globalPos() - offset;
        this->move(windowpos);
    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
    qDebug() << "catch wheel event " << endl;
    //鼠标滚动远离使用者放大textedit
    if(event->delta() > 0){
        qDebug() << "catch wheel event delta > 0" << endl;
        ui->textEdit->zoomIn();
    }else {
        qDebug() << "catch wheel event delta < 0" << endl;
        ui->textEdit->zoomOut();
    }
}

