#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MySyntaxHighlighter;
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
    MySyntaxHighlighter * m_ligher;
};

#endif // MAINWINDOW_H
