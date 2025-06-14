#include "User.h"
#include "Book.h"
#include <stdio.h>
#include <string.h>

// �����û�������methodΪ���ҷ�ʽ��foundBookΪ��Ų��ҽ�������飬iΪ��ǰ���ҽ��������
bool SearchUser(user User, userList L, char method, userList foundUser, int& i) {
	user* p = L->next;  // ָ������ĵ�һ���û�
	user* fu = foundUser;  // ���ڴ洢�ҵ����û�
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����false��ʾδ�ҵ��û�
	}
	if (i >= MAXSIZE) {  // ������ҵ����û����������������
		return true;  // ����true��ʾ���ҽ���
	}
	while (fu->next) {  // �ҵ����һ��λ��
		fu = fu->next;  // �ƶ�����һ��λ��
	}
	while (p) {
		switch (method) {  // ���ݷ��������û�
			case 'n':  // ���û�������
				if (strcmp(p->name, User.name) == 0) {
					user* newUser = new user(*p);  // �������û�
					fu->next = newUser;  // ���ҵ����û���Ϣ��������
					i++;  // �������ҵ����û�����
					return true;
				}
				break;
			case 'u':  // ���˺Ų���
				if (strcmp(p->username, User.username) == 0) {
					user* newUser = new user(*p);  // �������û�
					fu->next = newUser;  // ���ҵ����û���Ϣ��������
					i++;  // �������ҵ����û�����
					return true;
				}
				break;
			case 'p':  // ���������
				if (strcmp(p->password, User.password) == 0) {
					user* newUser = new user(*p);  // �������û�
					fu->next = newUser;  // ���ҵ����û���Ϣ��������
					i++;  // �������ҵ����û�����
					return true;
				}
				break;
			default:  // Ĭ�ϰ�ID����
				if (p->id == User.id) {
					user* newUser = new user(*p);  // �������û�
					fu->next = newUser;  // ���ҵ����û���Ϣ��������
					i++;  // �������ҵ����û�����
					return true;
				}
				break;
		}
		p = p->next;  // �ƶ�����һ���û�
	}
	if (i > 0) {  // ����ҵ��û�
		return true;  // ����true��ʾ���ҳɹ�
	}
	return false;  
}

// ����û�����
bool AddUser(user User, userList& L) {
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����false��ʾδ�ҵ��û�
	}
	user found[100];  // ���ڴ洢�ҵ����û�
	char temp = 'i';  // Ĭ�ϰ�ID����
	int i = 0;
	if (SearchUser(User, L, temp, found, i)) {  // ����û��Ѵ���
		return false;  // ���ʧ��
	}
	user* newUser = new user(User);  // �������û�
	newUser->next = L->next;  // �����û����뵽����ͷ��
	L->next = newUser;  // ��������ͷָ��
	return true;  // ��ӳɹ�
}

// ɾ���û�����
bool DeleteUser(user User, userList L) {
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����false��ʾδ�ҵ��û�
	}
	user* p = L->next;  // ָ������ĵ�һ���û�
	user* pre = L;  // ���ڼ�¼ǰһ���û�
	while (p) {
		if (p->id == User.id) {  // �ҵ�Ҫɾ�����û�
			pre->next = p->next;  // ɾ���û�
			delete p;  // �ͷ��ڴ�
			return true;  // ɾ���ɹ�
		}
		pre = p;  // �ƶ�����һ���û�
		p = p->next;
	}
	return false;  // δ�ҵ��û���ɾ��ʧ��
}

// �޸��û�����
bool ModifyUser(user UserPre, user UserMod, userList L) {
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����false��ʾδ�ҵ��û�
	}
	user* p = L->next;  // ָ������ĵ�һ���û�
	while (p) {
		if (p->id == UserPre.id) {  // �ҵ�Ҫ�޸ĵ��û�
			strcpy(p->name, UserPre.name);// �޸��û���
			strcpy(p->username, UserPre.username);// �޸��˺�
			strcpy(p->password, UserPre.password);// �޸�����
			return true;  // �޸ĳɹ�
		}
		p = p->next;  // �ƶ�����һ���û�
	}
	return false;  // δ�ҵ��û����޸�ʧ��
}

// ��ȡ�û������鼮����
bool GetUserBorrowedBooks(user User, bookList& L, bookList& foundBook, int& i) {
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����false��ʾδ�ҵ��鼮
	}
	book* p = L->next;  // ָ������ĵ�һ���鼮
	book* fb = foundBook;  // ���ڴ洢�ҵ����鼮
	while (fb->next) {  // �ҵ����һ��λ��
		fb = fb->next;  // �ƶ�����һ��λ��
	}
	while (p) {
		if (p->isBorrowed && p->id == User.id) {  // ����鼮��������IDƥ��
			book* newBook = new book(*p);  // �������鼮
			fb->next = newBook;  // ���ҵ����鼮��Ϣ��������
			i++;  // �������ҵ����鼮����
		}
		p = p->next;  // �ƶ�����һ���鼮
	}
	if (i > 0) {  // ����ҵ��鼮
		return true;  // ����true��ʾ���ҳɹ�
	}
	return false;
}