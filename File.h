#ifndef BOOKFILE
#define BOOKFILE
#define BOOKPATH "Book.csv"
#define USERPATH "User.csv"
#define ADMINPATH "Admin.csv"
#include "Book.h"
#include "User.h"

bookList readBookFile(const char* fileName);//��ȡ�ļ���������ͷָ��
void writeBookFile(const char* fileName, bookList head);//������д���ļ����洢ʱid��1��ʼ������

userList readUserFile(const char* fileName);//��ȡ�ļ���������ͷָ��
void writeUserFile(const char* fileName, userList head);//������д���ļ����洢ʱid��1��ʼ������

#endif // !BOOKFILE
