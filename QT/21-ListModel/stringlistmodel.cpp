#include "stringlistmodel.h"

StringListModel::StringListModel(const QStringList & strings,
                                 QObject* parent):
    QAbstractListModel(parent), stringList(strings)
{

}

int StringListModel::rowCount(const QModelIndex& parent ) const{
    return stringList.count();
}

QVariant StringListModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }

    if(index.row() >= stringList.size()){
        return QVariant();
    }

    if(role == Qt::DisplayRole || role == Qt::EditRole){
        return stringList.at(index.row());
    }else{
        return QVariant();
    }
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation,
                                     int role ) const{
    if(role != Qt::DisplayRole){
        return QVariant();
    }

    if(orientation == Qt::Horizontal){
        return QString("Column %1").arg(section);
    }else{
        return QString("Row %1").arg(section);
    }
}

Qt::ItemFlags  StringListModel::flags(const QModelIndex& index) const{
    //索引无效可以接受放入操作
    if(!index.isValid())
         return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    //索引有效，可以接受拖拽和放入操作
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable
            | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

bool StringListModel::setData(const QModelIndex& index,
                              const QVariant &value, int role ){
    if(index.isValid() && role == Qt::EditRole){
        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool StringListModel::insertRows(int position, int rows,
                                 const QModelIndex & index ){
    beginInsertRows(QModelIndex(), position, position + rows -1);
    for(int row = 0; row < rows; ++ row){
        stringList.insert(position, "");
    }
    endInsertRows();
    return true;
}
bool StringListModel::removeRows(int position, int rows,
                                 const QModelIndex & index ){
    beginRemoveRows(QModelIndex(), position, position+ rows-1);
    for(int row=0; row < rows; ++ row){
        stringList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

//拖放时导出的类型
QStringList StringListModel:: mimeTypes() const{
    QStringList types;
    //自定义类型
    types << "application/zack.list";
    return types;
}

//将拖放的数据放入mimedata中
QMimeData *StringListModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData * mimeData = new QMimeData();
    //字节数组
    QByteArray encodeData;
    QDataStream stream(&encodeData, QIODevice::WriteOnly);
    foreach(const QModelIndex& index, indexes){
        if(index.isValid()){
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    //将数据放入到QMimeData中
    mimeData->setData("application/zack.list", encodeData);
    return mimeData;

}

bool StringListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    //如果放入的动作是ignoreaction
    if(action == Qt::IgnoreAction){
        return true;
    }
    //如果数据的格式不是指定的格式，那么返回false
    if(!data->hasFormat("application/zack.list")){
        return false;
    }

    //因为这里是列表， 只用一列， 所以列大于0时返回false
    if(column > 0){
        return false;
    }

    //设置开始插入行
    int beginRow;
    if(row != -1){
        beginRow = row;
    }else if(parent.isValid()){
        beginRow = parent.row();
    }else {
        beginRow = rowCount(QModelIndex());
    }

    //将数据从QMimeData 中读取出来， 然后插入到模型中
    QByteArray encodeData = data->data("application/zack.list");
    //stream流
    QDataStream stream(&encodeData, QIODevice::ReadOnly);
    //统计插入的数据
    QStringList newItems;
    //统计插入的行数
    int rows = 0;
    while(!stream.atEnd()){
        QString text;
        stream >> text;
        newItems << text;
        ++ rows;
    }
    //插入指定行数
    insertRows(beginRow, rows, QModelIndex());
    //批量修改行数数据
    foreach(const QString& text, newItems){
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx,text);
        beginRow++;
    }

    return true;
}

Qt::DropActions StringListModel::supportedDropActions() const
{
    //设置支持放入动作,允许copy和move
    return Qt::CopyAction | Qt::MoveAction;
}

