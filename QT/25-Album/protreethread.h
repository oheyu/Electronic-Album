#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H
#include <QThread>
#include <QObject>
#include <QTreeWidgetItem>
#include <QTreeWidget>
class ProTreeThread : public QThread
{
    Q_OBJECT
public:

    explicit ProTreeThread(const QString &src_path, const QString & dist_path, QTreeWidgetItem *parent_item,
                           int &file_count,QTreeWidget* self,QTreeWidgetItem* root, QObject *parent = nullptr);


    ~ProTreeThread();
protected:
     virtual void run();
private:
     void CreateProTree(const QString& src_path, const QString& dist_path,
                              QTreeWidgetItem* parent_item,
                              int &file_count, QTreeWidget* self, QTreeWidgetItem* root, QTreeWidgetItem* preItem = nullptr);


    QString _src_path;
    QString _dist_path;
    int _file_count;
    QTreeWidgetItem * _parent_item;
    QTreeWidget* _self;
    QTreeWidgetItem* _root;
    bool _bstop;

public slots:
    void SlotCancelProgress();

signals:
    void SigUpdateProgress(int);
    void SigFinishProgress(int);

};

#endif // PROTREETHREAD_H
