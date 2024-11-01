#ifndef MYEDIT_H
#define MYEDIT_H

#include <QObject>
#include <QLineEdit>
#include <QKeyEvent>
class MyEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyEdit(QWidget *parent = nullptr);

protected:
   void keyPressEvent(QKeyEvent *);
   bool event(QEvent * event);
signals:

public slots:
};

#endif // MYEDIT_H
