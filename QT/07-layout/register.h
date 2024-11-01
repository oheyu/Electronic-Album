#ifndef REGISTER_H
#define REGISTER_H
#include <memory>
#include <QDialog>
using namespace std;
class Login;
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    void set_login(const  weak_ptr<Login> &login);
    void slot_register();
private:
    Ui::Register *ui;
    std::weak_ptr<Login> _login;
};

#endif // REGISTER_H
