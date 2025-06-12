#ifndef USER
#define USER

typedef struct Admin {
	char* username;
	char* password;
	Admin* next;
}Admin,*AdminList;

typedef struct User {
	char* username;
	char* password;
	User* next;
}User,*UserList;

#endif // !USER
