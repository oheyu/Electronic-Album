#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::ClickFocus);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event){
    //判断是ctrl+M
    if(event->modifiers() == Qt::ControlModifier){
        if(event->key() == Qt::Key_M  && windowState() != Qt::WindowFullScreen){
            setWindowState(Qt::WindowFullScreen);
            return;
        }
        return;
    }

    //如果按下的是ESC
    if(event->key() == Qt::Key_Escape && windowState() == Qt::WindowFullScreen){
        setWindowState(Qt::WindowNoState);
        return;
    }

    bool b_upflag= false;
    bool b_downflag = false;
    bool b_leftflag = false;
    bool b_rightflag = false;

    if(event->key() == Qt::Key_Up){
        if(event->isAutoRepeat()){
            auto curpos = ui->pushButton->pos();
            curpos.setY(curpos.y()-5);
            ui->pushButton->move(curpos);
            return;
        }else{
            b_upflag = true;
        }

    }

    if(event->key() == Qt::Key_Left){
        if(event->isAutoRepeat()){
            auto curpos = ui->pushButton->pos();
            curpos.setX(curpos.x()-5);
            ui->pushButton->move(curpos);
            return;
        }else{
            b_leftflag = true;
        }
    }


    if(event->key() == Qt::Key_Down){
        if(event->isAutoRepeat()){
            auto curpos = ui->pushButton->pos();
            curpos.setY(curpos.y()+5);
            ui->pushButton->move(curpos);
            return;
        }else{
            b_downflag = true;
        }

    }

    if(event->key() == Qt::Key_Right){
        if(event->isAutoRepeat()){
            auto curpos = ui->pushButton->pos();
            curpos.setX(curpos.x()+5);
            ui->pushButton->move(curpos);
            return;
        }else{
            b_rightflag = true;
        }
    }

    auto curpos = ui->pushButton->pos();
    if(b_upflag){
        curpos.setY(curpos.y()-5);
    }

    if(b_downflag){
        curpos.setY(curpos.y()+5);
    }

    if(b_leftflag){
        curpos.setX(curpos.x()-5);
    }

    if(b_rightflag){
        curpos.setX(curpos.x()+5);
    }

     ui->pushButton->move(curpos);

}


void Widget::keyReleaseEvent(QKeyEvent *event){

}
