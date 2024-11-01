#include "mysyntaxhighlighter.h"
#include <QFont>

MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument* parent):QSyntaxHighlighter (parent)
{

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myFormat;
    myFormat.setFont(QFont("微软雅黑"));
    myFormat.setFontWeight(QFont::Bold);
    myFormat.setForeground(Qt::green);
    //匹配char
    QString pattern = "\\bchar\\b";
    //创建正则表达式
    QRegExp express(pattern);
    //从索引0的位置开始匹配
    int index = text.indexOf(express);
    while (index>0) {
        int matchLen = express.matchedLength();
        //对匹配的字符串设置高亮
        setFormat(index, matchLen, myFormat);
        index = text.indexOf(express, index+matchLen);
    }
}



