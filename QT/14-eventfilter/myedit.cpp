#include "myedit.h"
#include <QDebug>
#include <QMessageBox>
MyEdit::MyEdit(QWidget *parent) : QLineEdit(parent)
{

}


void MyEdit::keyPressEvent(QKeyEvent * event){
    qDebug()<<"MyEdit key press event";
    QLineEdit::keyPressEvent(event);
    event->ignore();
}

bool MyEdit::event(QEvent *pevent)
{
    if(pevent->type() == QEvent::KeyPress){
        qDebug() << tr("my edit event") << endl;
    }

    return  QLineEdit::event(pevent);
}
