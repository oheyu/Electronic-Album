#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QObject>
#include "myedit.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject* object, QEvent* event);
private:
    Ui::Widget *ui;
    MyEdit* line_edit_;
};

#endif // WIDGET_H
