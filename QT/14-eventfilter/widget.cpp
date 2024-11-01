#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    line_edit_ = new MyEdit(this);
    line_edit_->move(100,100);
    line_edit_->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent * event){
    qDebug()<<"Widget key press event" << endl;
}

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    if(object == line_edit_){
        if(event->type() == QEvent::KeyPress){
            qDebug() << "widget eventfilter catch line_edit" << endl;
            return false;
        }
    }

    return QWidget::eventFilter(object, event);
}
