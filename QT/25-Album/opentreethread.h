#ifndef OPENTREETHREAD_H
#define OPENTREETHREAD_H

#include <QThread>
#include <QObject>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
class OpenTreeThread:public QThread
{
     Q_OBJECT
public:
    explicit OpenTreeThread(const QString&src_path, int &file_count,
                           QTreeWidget* self,QObject *parent = nullptr);
    void OpenProTree(const QString &src_path,
                                    int &file_count, QTreeWidget *self);
protected:
     virtual void run();
private:
    void RecursiveProTree(const QString &src_path,
                          int &file_count, QTreeWidget *self,
                          QTreeWidgetItem* root, QTreeWidgetItem* parent, QTreeWidgetItem* preitem);
    QString _src_path;
    int _file_count;
    QTreeWidget* _self;
    bool _bstop;
    QTreeWidgetItem* _root;
signals:
     void SigFinishProgress(int);
     void SigUpdateProgress(int);
};

#endif // OPENTREETHREAD_H
