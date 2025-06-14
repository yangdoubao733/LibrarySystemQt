#ifndef BOOKFILE
#define BOOKFILE
#define BOOKPATH "Book.csv"
#define USERPATH "User.csv"
#define ADMINPATH "Admin.csv"
#include "Book.h"
#include "User.h"

bookList readBookFile(const char* fileName);//读取文件返回链表头指针
void writeBookFile(const char* fileName, book* head);//将链表写入文件

UserList readUserFile(const char* fileName);//读取文件返回链表头指针
void writeUserFile(const char* fileName, book* head);//将链表写入文件

AdminList readAdminFile(const char* fileName);//读取文件返回链表头指针
void writeAdminFile(const char* fileName, book* head);//将链表写入文件

#endif // !BOOKFILE
