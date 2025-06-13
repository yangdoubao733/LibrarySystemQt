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

// �����û�������methodΪ���ҷ�ʽ��foundBookΪ��Ų��ҽ�������飬iΪ��ǰ���ҽ��������
bool SearchUser(user User, userList L, char method, userList foundUser, int& i);

// ���ͼ�麯��
bool AddUser(user User, userList& L);

// ɾ��ͼ�麯��
bool DeleteUser(user User, userList L);

// �޸�ͼ�麯��
bool ModifyUser(user UserPre, user UserMod, userList L);

// ��ȡ�û������鼮����
bool GetUserBorrowedBooks(user User, bookList& L, bookList& foundBook, int& i);
#endif // !USER
