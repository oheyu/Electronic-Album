#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Register;
class Login : public QDialog, public std::enable_shared_from_this<Login>
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void initSignals();
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
    std::shared_ptr<Register> _register;
};
#endif // LOGIN_H
