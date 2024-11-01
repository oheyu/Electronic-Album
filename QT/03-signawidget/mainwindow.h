#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class ChildDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void showChildDialog();
    void showMainDialog();
private:
    ChildDialog *_child_dialog;
};

#endif // MAINWINDOW_H
