#ifndef MYACTION_H
#define MYACTION_H
#include <QWidgetAction>
#include <QLineEdit>
#include <QObject>
class MyAction: public QWidgetAction
{
Q_OBJECT
signals:
   void  getText(const QString& string);
public:
    MyAction(QObject * parent = nullptr);
protected:
    virtual QWidget * createWidget(QWidget* parent);
private:
    QLineEdit * lineEdit;
private slots:
    void sendText();
};

#endif // MYACTION_H
