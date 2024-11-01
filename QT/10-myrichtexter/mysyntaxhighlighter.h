#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextDocument>
class MySyntaxHighlighter:public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit MySyntaxHighlighter(QTextDocument* parent = 0);
    //重写实现高亮
protected:
    void highlightBlock(const QString& text);
};

#endif // MYSYNTAXHIGHLIGHTER_H
