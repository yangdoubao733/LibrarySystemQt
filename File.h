#ifndef BOOKFILE
#define BOOKFILE
#define BOOKPATH "Book.csv"
#define USERPATH "User.csv"
#define ADMINPATH "Admin.csv"
#include "Book.h"
#include "User.h"

bookList readBookFile(const char* fileName);//��ȡ�ļ���������ͷָ��
void writeBookFile(const char* fileName, book* head);//������д���ļ�

UserList readUserFile(const char* fileName);//��ȡ�ļ���������ͷָ��
void writeUserFile(const char* fileName, book* head);//������д���ļ�

AdminList readAdminFile(const char* fileName);//��ȡ�ļ���������ͷָ��
void writeAdminFile(const char* fileName, book* head);//������д���ļ�

#endif // !BOOKFILE
