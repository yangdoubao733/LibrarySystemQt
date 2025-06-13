#include "login.h"
#include "ui_login.h"
#include "adminmainwindow.h"
#include "usermainwindow.h"
#include <qstring.h>
#include <stdio.h>
#include "File.h"
#include <iostream>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("ͼ��ݹ���ϵͳ");
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
    //�ж��Ƿ��ǹ���Ա
    adminList alist;
    alist = readAdminFile(ADMINPATH);
    admin* a = alist->next;
    while (a && flag == 0) {
        QString username(a->username);
        QString password(a->password);
        if (QString::compare(current_username, username) == 0 && QString::compare(current_password, password) == 0) {
            admin* temp = alist;
            while (alist) { //���������ڴ�
                temp = alist->next;
                delete alist;
                alist = temp;
            }
            flag = 1;
            AdminMainWindow amw;
            this->close();
            amw.show();
        }
        a = a->next;
    }
    //�ж��Ƿ�Ϊ��ͨ�û�
    userList ulist;
    ulist = readUserFile(USERPATH);
    user* u = ulist->next;
    while (u && flag == 0) {
        QString username(u->username);
        QString password(u->password);
        if (QString::compare(current_username, username) == 0 && QString::compare(current_password, password) == 0) {
            user* temp = ulist;
            while (ulist) { //���������ڴ�
                temp = ulist->next;
                delete ulist;
                ulist = temp;
            }
            flag = 1;
            UserMainWindow umw;
            this->close();
            umw.show();
        }
        u = u->next;
    }
}

