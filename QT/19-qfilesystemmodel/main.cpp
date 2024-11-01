#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QSplitter * splitter  = new QSplitter;
    QFileSystemModel * model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    QTreeView * tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    QListView * list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    splitter->setWindowTitle("Two views onto the same file system model");
    splitter->resize(1000,800);
    splitter->show();
    return a.exec();
}
