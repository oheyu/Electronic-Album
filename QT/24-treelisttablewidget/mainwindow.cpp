#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QListWidgetItem>
#include <QPixmap>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto listWidget = new QListWidget(this);
    QListWidgetItem * listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText("listItem");
    QPixmap pixmap(50,50);
    pixmap.fill(Qt::blue);
    listWidgetItem->setIcon(pixmap);
    listWidgetItem->setToolTip("this is list item");
    listWidget->insertItem(1,listWidgetItem);

    QListWidgetItem * listWidgetItem2 = new QListWidgetItem;
    listWidgetItem2->setText("listItem2");
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    listWidgetItem2->setIcon(pixmap2);
    listWidgetItem2->setToolTip("this is list item2");
    listWidget->insertItem(2,listWidgetItem2);

    listWidget->sortItems(Qt::DescendingOrder);
    listWidget->show();
    this->setCentralWidget(listWidget);

    //设置list为单选模式
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //启用拖动
    listWidget->setDragEnabled(true);
    //设置接受拖放
    listWidget->viewport()->setAcceptDrops(true);
    //设置显示将要放置的位置
    listWidget->setDropIndicatorShown(true);
    //设置拖放模式为移动项目，如果不设置，则为复制项目
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);


    _treeWidget = new QTreeWidget();
    //treewidget 要设置列数
    _treeWidget->setColumnCount(2);
    QStringList headers;
    headers << "name" << "year";
    _treeWidget->setHeaderLabels(headers);

    //添加项目

    //父节点是_treeWidget
    QTreeWidgetItem * grade1 = new QTreeWidgetItem(_treeWidget);
    grade1->setText(0,"Grade1");
    //父节点是grade1
    QTreeWidgetItem * student = new QTreeWidgetItem(grade1);
    student->setText(0,"Tom");
    student->setText(1,"1996");

    //父节点是grade1, 在student之后
    QTreeWidgetItem * student2 = new QTreeWidgetItem(grade1, student);
    student2->setText(0,"Zack");
    student2->setText(1,"1988");
    //父节点是_treeWidget, 在grade1之后
    QTreeWidgetItem * grade2 = new QTreeWidgetItem(_treeWidget,grade1);
    grade2->setText(0,"Grade2");

    QTreeWidgetItem * student3 = new QTreeWidgetItem(grade1, student2);
    student3->setText(0,"Will");
    student3->setText(1,"1989");
    //删除student3,先获取其父节点
    auto *parent_student3 = student3->parent();
    //获取student3在其父节点下的index
    auto index_student3 = parent_student3->indexOfChild(student3);
    //根据index删除student3
    delete parent_student3->takeChild(index_student3);
    _treeWidget->show();

    //删除grade2
    auto * parent_grade2 = grade2->parent();
    //grade2为顶层节点，所以其父节点必为null
    assert(parent_grade2 == nullptr);
    //通过treewidget获取grade2的index
    auto index_grade2 = _treeWidget->indexOfTopLevelItem(grade2);
    delete _treeWidget->takeTopLevelItem(index_grade2);

    //创建表格指定行号和列号
   _tableWidget =  new QTableWidget(3,2);
    //创建表格项目，将其插入到表格中
    QTableWidgetItem * tableWidgetItem = new QTableWidgetItem("qt");
    _tableWidget->setItem(1,1,tableWidgetItem);
    //创建表头
    QTableWidgetItem * headerV = new QTableWidgetItem("first");
    _tableWidget->setVerticalHeaderItem(0, headerV);
    QTableWidgetItem * headerH = new QTableWidgetItem("ID");
    _tableWidget->setHorizontalHeaderItem(0, headerH);
    _tableWidget->show();
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow Destruction";
    delete ui;
    delete  _treeWidget;
    delete  _tableWidget;
}
