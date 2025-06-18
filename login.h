#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
QString login_UserName;
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:

    void on_loginButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
