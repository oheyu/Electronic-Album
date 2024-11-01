#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimerEvent>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void timerEvent(QTimerEvent* event);
    void slot_update_lcd();
private:
    Ui::Widget *ui;
    int id1;
    int id2;
    int id3;
};

#endif // WIDGET_H
