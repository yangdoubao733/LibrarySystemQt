#ifndef BOOKFILE
#define BOOKFILE
#define BOOKPATH "Book.csv"
#define USERPATH "User.csv"
#define ADMINPATH "Admin.csv"
#include "Book.h"
#include "User.h"

bookList readBookFile(const char* fileName);//读取文件返回链表头指针
void writeBookFile(const char* fileName, bookList head);//将链表写入文件（存储时id从1开始递增）

userList readUserFile(const char* fileName);//读取文件返回链表头指针
void writeUserFile(const char* fileName, userList head);//将链表写入文件（存储时id从1开始递增）

adminList readAdminFile(const char* fileName);// 读取管理员文件，返回带头节点的管理员链表

#endif // !BOOKFILE
