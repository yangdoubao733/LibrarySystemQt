#include "User.h"
#include "Book.h"
#include <stdio.h>
#include <string.h>

// 查找用户函数，method为查找方式，foundBook为存放查找结果的数组，i为当前查找结果的数量
bool SearchUser(user UserToFind, userList L, char method, userList foundUser, int& i) {
	user* p = L->next;  // 指向链表的第一个用户
	user* fu = foundUser;  // 用于存储找到的用户
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回false表示未找到用户
	}
	if (i >= MAXSIZE) {  // 如果已找到的用户数量超过最大限制
		return true;  // 返回true表示查找结束
	}
	while (fu->next) {  // 找到最后一个位置
		fu = fu->next;  // 移动到下一个位置
	}
	while (p) {
		switch (method) {  // 根据方法查找用户
			case 'n':  // 按用户名查找
				if (strcmp(p->name, UserToFind.name) == 0) {
					user* newUser = new user(*p);  // 创建新用户
					fu->next = newUser;  // 将找到的用户信息存入数组
					i++;  // 增加已找到的用户数量
					return true;
				}
				break;
			case 'u':  // 按账号查找
				if (strcmp(p->username, UserToFind.username) == 0) {
					user* newUser = new user(*p);  // 创建新用户
					fu->next = newUser;  // 将找到的用户信息存入数组
					i++;  // 增加已找到的用户数量
					return true;
				}
				break;
			case 'p':  // 按密码查找
				if (strcmp(p->password, UserToFind.password) == 0) {
					user* newUser = new user(*p);  // 创建新用户
					fu->next = newUser;  // 将找到的用户信息存入数组
					i++;  // 增加已找到的用户数量
					return true;
				}
				break;
			default:  // 默认按ID查找
				if (p->id == UserToFind.id) {
					user* newUser = new user(*p);  // 创建新用户
					fu->next = newUser;  // 将找到的用户信息存入数组
					i++;  // 增加已找到的用户数量
					return true;
				}
				break;
		}
		p = p->next;  // 移动到下一个用户
	}
	if (i > 0) {  // 如果找到用户
		return true;  // 返回true表示查找成功
	}
	return false;  
}

// 添加用户函数
bool AddUser(user UserToCreate, userList& L) {
	userList found = new user;  // 用于存储找到的用户
	found->next = NULL;
	char temp = 'n';  // 默认按ID查找
	int i = 0;
	if (SearchUser(UserToCreate, L, temp, found, i)) {  // 如果用户已存在
		return false;  // 添加失败
	}
	user* newUser = new user;  // 创建新用户
	newUser->name = strdup(UserToCreate.name);
	newUser->username = strdup(UserToCreate.username);
	newUser->password = strdup(UserToCreate.password);
	newUser->next = L->next;  // 将新用户插入到链表头部
	L->next = newUser;  // 更新链表头指针
	return true;  // 添加成功
}

// 删除用户函数
bool DeleteUser(user UserToDelete, userList L) {
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回false表示未找到用户
	}
	user* p = L->next;  // 指向链表的第一个用户
	user* pre = L;  // 用于记录前一个用户
	while (p) {
		if (p->id == UserToDelete.id) {  // 找到要删除的用户
			pre->next = p->next;  // 删除用户
			delete p;  // 释放内存
			return true;  // 删除成功
		}
		pre = p;  // 移动到下一个用户
		p = p->next;
	}
	return false;  // 未找到用户，删除失败
}

// 修改用户函数
bool ModifyUser(user UserPre, user UserMod, userList L) {
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回false表示未找到用户
	}
	user* p = L->next;  // 指向链表的第一个用户
	while (p) {
		if (p->id == UserPre.id) {  // 找到要修改的用户
			strcpy(p->name, UserPre.name);// 修改用户名
			strcpy(p->username, UserPre.username);// 修改账号
			strcpy(p->password, UserPre.password);// 修改密码
			return true;  // 修改成功
		}
		p = p->next;  // 移动到下一个用户
	}
	return false;  // 未找到用户，修改失败
}

// 获取用户借阅书籍函数
bool GetUserBorrowedBooks(user User, bookList& L, bookList& foundBook, int& i) {
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回false表示未找到书籍
	}
	book* p = L->next;  // 指向链表的第一个书籍
	book* fb = foundBook;  // 用于存储找到的书籍
	while (fb->next) {  // 找到最后一个位置
		fb = fb->next;  // 移动到下一个位置
	}
	while (p) {
		if (p->isBorrowed && p->id == User.id) {  // 如果书籍被借阅且ID匹配
			book* newBook = new book(*p);  // 创建新书籍
			fb->next = newBook;  // 将找到的书籍信息存入数组
			i++;  // 增加已找到的书籍数量
		}
		p = p->next;  // 移动到下一个书籍
	}
	if (i > 0) {  // 如果找到书籍
		return true;  // 返回true表示查找成功
	}
	return false;
}