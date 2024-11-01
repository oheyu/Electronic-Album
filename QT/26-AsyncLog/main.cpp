#include "mainwindow.h"
#include <QApplication>
#include "AsyncLog.h"
#include <csignal>

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

    auto & instance =  AsyncLog::AsyncLog::Instance();
    instance.AsyncWrite(AsyncLog::LogLv::ERRORS, "hello", "world !",
                        "my name is {} ", "zack {}", "fair");
    instance.start();

    MainWindow main;
    main.show();

    a.exec();
    qDebug() << "Application Quitting, Please Wait...";
    AsyncLog::AsyncLog::Instance().Stop();
    // 暂停执行500毫秒（0.5秒）
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    qDebug() << "Application exited...";
    return 0;

}
