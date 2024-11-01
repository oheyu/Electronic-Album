#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>

class QItemSelection;
class QModelIndex;
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
    QTableView* _table_view;
public slots:
    void getCurrentItemData();
    void toggleSelection();
    void updateSelection(const QItemSelection& selected, const QItemSelection& deselected);
    void changeCurrent(const QModelIndex& current, const QModelIndex& previous);
};

#endif // MAINWINDOW_H
