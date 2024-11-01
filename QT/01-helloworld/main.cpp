#include "hellodialog.h"
#include "hellodialog2.h"
#include "hellodialog3.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HelloDialog w;
    w.show();

    hellodialog2 w2;
    w2.move(300,300);
    w2.show();

    HelloDialog3 w3;
    w3.move(1200,300);
    w3.show();
    return a.exec();
}
