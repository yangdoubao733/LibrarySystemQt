#ifndef USER
#define USER

typedef struct admin {
	char* username;
	char* password;
	admin* next;
}admin,*adminList;

typedef struct User {
	int id;
	char* name;
	char* username;
	char* password;
	user* next;
}user,*userList;

// 查找用户函数，method为查找方式，foundBook为存放查找结果的数组，i为当前查找结果的数量
bool SearchUser(user User, userList L, char method, userList foundUser, int& i);

// 添加图书函数
bool AddUser(user User, userList& L);

// 删除图书函数
bool DeleteUser(user User, userList L);

// 修改图书函数
bool ModifyUser(user UserPre, user UserMod, userList L);

// 获取用户借阅书籍函数
bool GetUserBorrowedBooks(user User, bookList& L, bookList& foundBook, int& i);
#endif // !USER
