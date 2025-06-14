#include"Book.h"
#include<string.h>
bool SearchBook(book Book, bookList L, char method, bookList foundBook, int &i) {// 搜索图书函数,返回找到的图书信息，查找不到返回false
	book* p = L->next;
	book* fb = foundBook;  // 用于存储找到的图书
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回false表示未找到图书
	}
	if(i >= MAXSIZE) {  // 如果已找到的图书数量超过最大限制
		return true;  // 返回true表示查找结束
	}
	while (fb->next) {//找到最后一个位置
		fb = fb->next;  // 移动到下一个位置
	}
	while (p) {
		switch (method) {  // 根据方法查找图书
			case 'a':  // 按作者查找
				if (strcmp(p->author, Book.author) == 0) {
					book* newBook = new book(*p);  // 创建新图书
					fb->next = newBook;  // 将找到的图书信息存入数组
					fb = fb->next;  // 移动到下一个位置
					i++;  // 增加已找到的图书数量
				}
				break;
			case 'I':  // 按ISBN查找
				if (p->ISBN == Book.ISBN) {
					book* newBook = new book(*p);  // 创建新图书
					fb->next = newBook;  // 将找到的图书信息存入数组
					i++;  // 增加已找到的图书数量
					return true;
				}
				break;
			case 'n':  // 按书名查找
				if (strcmp(p->name, Book.name) == 0) {
					book* newBook = new book(*p);  // 创建新图书
					fb->next = newBook;  // 将找到的图书信息存入数组
					i++;  // 增加已找到的图书数量
					return true;
				}
				break;
			case 'y':  // 按出版年份查找
				if (p->year == Book.year) {
					book* newBook = new book(*p);  // 创建新图书
					fb->next = newBook;  // 将找到的图书信息存入数组
					fb = fb->next;  // 移动到下一个位置
					i++;  // 增加已找到的图书数量
				}
				break;
			
		}
		p = p->next;  // 移动到下一个图书
	}
	if (i > 0) {  // 如果找到图书
		return true;  // 返回true表示查找成功
	}
	return false;  
} 

bool AddBook(book Book, bookList &L) {  // 添加图书函数
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回-1表示未找到图书
	}
	book founded[100];  // 用于存储找到的图书
	char temp = 'n';  // 默认按书名查找
	int i = 0;
	if (SearchBook(Book, L, temp, founded,i)) {  // 如果图书已存在
		return false;  // 添加失败
	}
	book* newBook = new book(Book);  // 创建新图书
	newBook->next = L->next;  // 将新图书插入到链表头部
	L->next = newBook;  // 更新链表头指针
	return true;  // 添加成功
}

bool DeleteBook(book Book, bookList L) {  // 删除图书函数
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回-1表示未找到图书
	}
	book *p = L->next;
	book* prev = L;  // 前驱指针
	while (p) {
		if (p->id == Book.id) {  // 找到要删除的图书
			prev->next = p->next;  // 删除图书
			delete p;  // 释放内存
			return true;  // 删除成功
		}
		prev = p;  // 更新前驱指针
		p = p->next;  // 移动到下一个图书
	}
	return false;  // 删除失败，未找到图书
}

bool ModifyBook(book bookPre, book bookMod, bookList L) {  // 修改图书函数
	book* p = L->next;
	if (L->next == NULL) {  // 如果链表为空
		return false;  // 返回-1表示未找到图书
	}
	while (p) {
		if (p->id == bookPre.id) {  // 找到要修改的图书
			// 修改图书信息
			p->ISBN = bookMod.ISBN;
			strcpy(p->name, bookMod.name);
			strcpy(p->author, bookMod.author);
			strcpy(p->publisher, bookMod.publisher);
			p->year = bookMod.year;
			p->isBorrowed = bookMod.isBorrowed;
			return true;  // 修改成功
		}
		p = p->next;  // 移动到下一个图书
	}
	return false;  // 修改失败，未找到图书
}

int BorrowBook(book Book, bookList L, char* userName) {  // 借阅图书函数
	book* p = L->next;
	if (L->next == NULL) {  // 如果链表为空
		return -1;  // 返回-1表示未找到图书
	}
	while (p) {
		if (p->id == Book.id) {  // 找到要借阅的图书
			p->isBorrowed = true;  // 标记为已借阅
			p->borrowedBy = userName;  // 记录借阅者ID
			return true;  // 修改成功
		}
		p = p->next;  // 移动到下一个图书
	}
	return false;  // 借阅失败，未找到图书
}