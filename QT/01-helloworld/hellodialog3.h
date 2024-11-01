#ifndef HELLODIALOG3_H
#define HELLODIALOG3_H

#include <QDialog>

namespace Ui {
class HelloDialog3;
}

class HelloDialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit HelloDialog3(QWidget *parent = nullptr);
    ~HelloDialog3();

private:
    Ui::HelloDialog3 *ui;
};

#endif // HELLODIALOG3_H
