#include "User.h"
#include "Book.h"
#include <stdio.h>
// �����û�������methodΪ���ҷ�ʽ��foundBookΪ��Ų��ҽ�������飬iΪ��ǰ���ҽ��������
bool SearchUser(user User, userList L, char method, userList foundUser, int& i);

// ����û�����
bool AddUser(user User, userList& L);

// ɾ���û�����
bool DeleteUser(user User, userList L);

// �޸��û�����
bool ModifyUser(user UserPre, user UserMod, userList L);

// ��ȡ�û������鼮����
bool GetUserBorrowedBooks(user User, bookList& L, bookList& foundBook, int& i);