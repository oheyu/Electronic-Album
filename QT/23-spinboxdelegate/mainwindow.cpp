#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItem>
#include <QItemSelectionModel>
#include <QTableView>
#include "spinboxdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel * model = new QStandardItemModel(7,4,this);
    for(int row=0; row < 7; row++){
        for(int column = 0; column < 4; column++){
            QStandardItem * item = new QStandardItem(QString("%1").arg(row*4+column));
            model->setItem(row, column, item);
        }
    }

   QTableView* _table_view = new QTableView;
    _table_view->setModel(model);
    setCentralWidget(_table_view);
    this->resize(800,800);

    QTableView* _table_view2 = new QTableView;
    SpinBoxDelegate * delegate = new SpinBoxDelegate(this);
    QStandardItemModel * model2 = new QStandardItemModel(7,4,this);
    for(int row=0; row < 7; row++){
        for(int column = 0; column < 4; column++){
            QStandardItem * item = new QStandardItem(QString("%1").arg(row*4+column));
            model2->setItem(row, column, item);
        }
    }
     _table_view2->setModel(model2);
     _table_view2->setItemDelegate(delegate);
     _table_view2->show();
     _table_view2->resize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
