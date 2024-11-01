#include "mainwindow.h"

#include <QApplication>
#include "stringlistmodel.h"
#include <QListView>
#include <QTableView>
#include <QAbstractItemView>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    QStringList list;
    list <<"a" << "b" << "c";

    StringListModel model(list);
    model.insertRows(3,2);
    model.removeRows(0,1);
//    QListView  listView;
//    listView.setModel(&model);
//    listView.show();

//    QTableView tableView;
//    tableView.setModel(&model);
//    tableView.show();

    QListView listView;
    listView.setModel(&model);
    listView.show();
    //设置选择模式为单选
    listView.setSelectionMode(QAbstractItemView::ExtendedSelection);
    //设置可拖拽
    listView.setDragEnabled(true);
    //设置可拖放
    listView.setAcceptDrops(true);
    //设置显示拖放位置
    listView.setDropIndicatorShown(true);

    return a.exec();
}
