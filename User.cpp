#include "User.h"
#include "Book.h"
#include <stdio.h>
// 查找用户函数，method为查找方式，foundBook为存放查找结果的数组，i为当前查找结果的数量
bool SearchUser(user User, userList L, char method, userList foundUser, int& i);

// 添加用户函数
bool AddUser(user User, userList& L);

// 删除用户函数
bool DeleteUser(user User, userList L);

// 修改用户函数
bool ModifyUser(user UserPre, user UserMod, userList L);

// 获取用户借阅书籍函数
bool GetUserBorrowedBooks(user User, bookList& L, bookList& foundBook, int& i);