#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPrinter;
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
    void DoPrint();
    void DoPrintPreview();
    void PrintPreview(QPrinter* printer);
    void CreatePdf();

};

#endif // MAINWINDOW_H
