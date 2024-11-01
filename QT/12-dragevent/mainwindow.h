#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QMimeData>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    //拖动进入事件
    void dragEnterEvent(QDragEnterEvent * event);
    //放下事件
    void dropEvent(QDropEvent * event);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
