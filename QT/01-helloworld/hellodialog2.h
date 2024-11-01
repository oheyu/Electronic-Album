#ifndef HELLODIALOG2_H
#define HELLODIALOG2_H
#include <QDialog>
#include "ui_hellodialog2.h"
class hellodialog2 : public QDialog
{
public:
    hellodialog2();
    ~hellodialog2();
private:
    Ui::Dialog* _ui;
};

#endif // HELLODIALOG2_H
