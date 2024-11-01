#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDialog>
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
private slots:
    void showTextFrame();
    void showTextBlock();
    void setTextFont(bool checked);
    void insertTable();
    void insertList();
    void insertImage();
    void textFind();
    void findNext();

private:
    QLineEdit * lineEdit;
    QDialog* findDialog;
};

#endif // MAINWINDOW_H
