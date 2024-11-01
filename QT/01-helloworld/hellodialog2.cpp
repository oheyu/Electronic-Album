#include "hellodialog2.h"

hellodialog2::hellodialog2():_ui(new Ui::Dialog())
{
    _ui->setupUi(this);
}

hellodialog2::~hellodialog2()
{
    delete  _ui;
}
