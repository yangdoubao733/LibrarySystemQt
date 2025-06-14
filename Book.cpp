#include"Book.h"
#include<string.h>
bool SearchBook(book Book, bookList L, char method, bookList foundBook, int &i) {// ����ͼ�麯��,�����ҵ���ͼ����Ϣ�����Ҳ�������false
	book* p = L->next;
	book* fb = foundBook;  // ���ڴ洢�ҵ���ͼ��
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����false��ʾδ�ҵ�ͼ��
	}
	if(i >= MAXSIZE) {  // ������ҵ���ͼ�����������������
		return true;  // ����true��ʾ���ҽ���
	}
	while (fb->next) {//�ҵ����һ��λ��
		fb = fb->next;  // �ƶ�����һ��λ��
	}
	while (p) {
		switch (method) {  // ���ݷ�������ͼ��
			case 'a':  // �����߲���
				if (strcmp(p->author, Book.author) == 0) {
					book* newBook = new book(*p);  // ������ͼ��
					fb->next = newBook;  // ���ҵ���ͼ����Ϣ��������
					fb = fb->next;  // �ƶ�����һ��λ��
					i++;  // �������ҵ���ͼ������
				}
				break;
			case 'I':  // ��ISBN����
				if (p->ISBN == Book.ISBN) {
					book* newBook = new book(*p);  // ������ͼ��
					fb->next = newBook;  // ���ҵ���ͼ����Ϣ��������
					i++;  // �������ҵ���ͼ������
					return true;
				}
				break;
			case 'n':  // ����������
				if (strcmp(p->name, Book.name) == 0) {
					book* newBook = new book(*p);  // ������ͼ��
					fb->next = newBook;  // ���ҵ���ͼ����Ϣ��������
					i++;  // �������ҵ���ͼ������
					return true;
				}
				break;
			case 'y':  // ��������ݲ���
				if (p->year == Book.year) {
					book* newBook = new book(*p);  // ������ͼ��
					fb->next = newBook;  // ���ҵ���ͼ����Ϣ��������
					fb = fb->next;  // �ƶ�����һ��λ��
					i++;  // �������ҵ���ͼ������
				}
				break;
			
		}
		p = p->next;  // �ƶ�����һ��ͼ��
	}
	if (i > 0) {  // ����ҵ�ͼ��
		return true;  // ����true��ʾ���ҳɹ�
	}
	return false;  
} 

bool AddBook(book Book, bookList &L) {  // ���ͼ�麯��
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����-1��ʾδ�ҵ�ͼ��
	}
	book founded[100];  // ���ڴ洢�ҵ���ͼ��
	char temp = 'n';  // Ĭ�ϰ���������
	int i = 0;
	if (SearchBook(Book, L, temp, founded,i)) {  // ���ͼ���Ѵ���
		return false;  // ���ʧ��
	}
	book* newBook = new book(Book);  // ������ͼ��
	newBook->next = L->next;  // ����ͼ����뵽����ͷ��
	L->next = newBook;  // ��������ͷָ��
	return true;  // ��ӳɹ�
}

bool DeleteBook(book Book, bookList L) {  // ɾ��ͼ�麯��
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����-1��ʾδ�ҵ�ͼ��
	}
	book *p = L->next;
	book* prev = L;  // ǰ��ָ��
	while (p) {
		if (p->id == Book.id) {  // �ҵ�Ҫɾ����ͼ��
			prev->next = p->next;  // ɾ��ͼ��
			delete p;  // �ͷ��ڴ�
			return true;  // ɾ���ɹ�
		}
		prev = p;  // ����ǰ��ָ��
		p = p->next;  // �ƶ�����һ��ͼ��
	}
	return false;  // ɾ��ʧ�ܣ�δ�ҵ�ͼ��
}

bool ModifyBook(book bookPre, book bookMod, bookList L) {  // �޸�ͼ�麯��
	book* p = L->next;
	if (L->next == NULL) {  // �������Ϊ��
		return false;  // ����-1��ʾδ�ҵ�ͼ��
	}
	while (p) {
		if (p->id == bookPre.id) {  // �ҵ�Ҫ�޸ĵ�ͼ��
			// �޸�ͼ����Ϣ
			p->ISBN = bookMod.ISBN;
			strcpy(p->name, bookMod.name);
			strcpy(p->author, bookMod.author);
			strcpy(p->publisher, bookMod.publisher);
			p->year = bookMod.year;
			p->isBorrowed = bookMod.isBorrowed;
			return true;  // �޸ĳɹ�
		}
		p = p->next;  // �ƶ�����һ��ͼ��
	}
	return false;  // �޸�ʧ�ܣ�δ�ҵ�ͼ��
}

int BorrowBook(book Book, bookList L, char* userName) {  // ����ͼ�麯��
	book* p = L->next;
	if (L->next == NULL) {  // �������Ϊ��
		return -1;  // ����-1��ʾδ�ҵ�ͼ��
	}
	while (p) {
		if (p->id == Book.id) {  // �ҵ�Ҫ���ĵ�ͼ��
			p->isBorrowed = true;  // ���Ϊ�ѽ���
			p->borrowedBy = userName;  // ��¼������ID
			return true;  // �޸ĳɹ�
		}
		p = p->next;  // �ƶ�����һ��ͼ��
	}
	return false;  // ����ʧ�ܣ�δ�ҵ�ͼ��
}