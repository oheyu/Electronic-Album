#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QWheelEvent>
#include <qDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event){

    if(watched == ui->textEdit){
        if(event->type() == QEvent::Wheel){
           QWheelEvent* wheelEvent  = static_cast<QWheelEvent*>(event);
            if(wheelEvent->delta() > 0){
                qDebug() << "catch wheel event delta > 0" << endl;
                ui->textEdit->zoomIn();
            }else {
                qDebug() << "catch wheel event delta < 0" << endl;
                ui->textEdit->zoomOut();
            }
            return true;
        }

        return false;
    }

    if(watched == ui->spinBox){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent * keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Space){
                ui->spinBox->setValue(0);
                return true;
            }
            return false;
        }
        return false;
    }

    return QWidget::eventFilter(watched, event);
}

