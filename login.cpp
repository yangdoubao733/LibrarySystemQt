#include "login.h"
#include "ui_login.h"
#include "adminmainwindow.h"
#include "usermainwindow.h"
#include <qstring.h>
#include <stdio.h>
#include "File.h"
#include <iostream>

QString login_UserName;

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("图书馆管理系统");
}

login::~login()
{
    delete ui;
}


void login::on_loginButton_clicked()
{
    int flag = 0;
    QString current_username = ui->userName->text();
    QString current_password = ui->password->text();
    //判断是否是管理员
    adminList alist;
    alist = readAdminFile(ADMINPATH);
    if (alist) {
        admin* a = alist->next;
        while (a && flag == 0) {
            QString username(a->username);
            QString password(a->password);
            if (QString::compare(current_username, username) == 0 && QString::compare(current_password, password) == 0) {
                admin* temp = alist;
                while (alist) { //清理链表内存
                    temp = alist->next;
                    delete alist;
                    alist = temp;
                }
                flag = 1;
                AdminMainWindow* amw = new AdminMainWindow();
                amw->show();
                this->close();
                
            }
            a = a->next;
        }
    }
    //判断是否为普通用户
    userList ulist;
    ulist = readUserFile(USERPATH);
    if (ulist) {
        user* u = ulist->next;
        while (u && flag == 0) {
            QString username(u->username);
            QString password(u->password);
            if (QString::compare(current_username, username) == 0 && QString::compare(current_password, password) == 0) {
                login_UserName = current_username; //保存当前登录的用户名
                user* temp = ulist;
                while (ulist) { //清理链表内存
                    temp = ulist->next;
                    delete ulist;
                    ulist = temp;
                }
                flag = 1;
                UserMainWindow* umw = new UserMainWindow();
                umw->show();
                this->close();
                
            }
            u = u->next;
        }
    }
}

