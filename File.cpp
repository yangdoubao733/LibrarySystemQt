#include "File.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 辅助函数：去除字符串首尾的空白字符
char* trim(char* str) {
    char* end;
    // 去除开头空白字符
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')) {
        str++;
    }
    if (*str == 0) {  // 全部是空白字符的情况
        return str;
    }
    // 去除末尾空白字符
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        end--;
    }
    *(end + 1) = '\0';  // 在末尾添加字符串结束符
    return str;
}


// 读取图书文件，返回图书链表头指针
bookList readBookFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");  // 以只读方式打开文件
    if (file == NULL) {
        return NULL;  // 文件打开失败，返回空指针
    }

    // 创建头节点（哨兵节点）
    bookList head = (bookList)malloc(sizeof(book));
    if (head == NULL) {
        fclose(file);
        return NULL;
    }
    head->next = NULL;
    bookList tail = head;  // 尾指针用于高效追加

    char line[1024];  // 行缓冲区

    // 跳过CSV标题行（如果有）
    fgets(line, sizeof(line), file);

    // 逐行读取数据
    while (fgets(line, sizeof(line), file)) {
        // 创建新节点
        bookList newNode = (bookList)malloc(sizeof(book));
        if (newNode == NULL) {
            fclose(file);
            return head;  // 返回已读取的部分链表
        }

        // 初始化指针成员
        newNode->name = NULL;
        newNode->author = NULL;
        newNode->publisher = NULL;
        newNode->borrowedBy = NULL;
        newNode->next = NULL;

        char* token;
        // 读取图书ID
        token = strtok(line, ",");
        if (token == NULL) continue;
        newNode->id = atoi(trim(token));

        // 读取图书名称（动态分配内存）
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->name = strdup(trim(token));

        // 读取作者（动态分配内存）
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->author = strdup(trim(token));

        // 读取出版社（动态分配内存）
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->publisher = strdup(trim(token));

        // 读取出版年份
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->year = atoi(trim(token));

        // 读取ISBN
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->ISBN = atoi(trim(token));

        // 读取借阅状态
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->isBorrowed = (strcmp(trim(token), "true") == 0);

        // 读取借阅者（动态分配内存）
        token = strtok(NULL, ",");
        if (token != NULL) {
            newNode->borrowedBy = strdup(trim(token));
        }
        else {
            newNode->borrowedBy = NULL;
        }

        // 将新节点添加到链表尾部
        tail->next = newNode;
        tail = newNode;
    }

    fclose(file);
    return head;  // 返回带头节点的链表
}

// 将图书链表写入文件
void writeBookFile(const char* fileName, bookList head) {
    FILE* file = fopen(fileName, "w");  // 以写入方式打开文件
    if (file == NULL || head == NULL) {
        return;  // 文件打开失败或链表为空，直接返回
    }

    // 写入CSV标题行
    fprintf(file, "ID,Name,Author,Publisher,Year,ISBN,IsBorrowed,BorrowedBy\n");
	int id = 1;  // 从1开始递增ID
    // 遍历链表（跳过哨兵节点）
    bookList current = head->next;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s,%d,%d,%s,%s\n",
            id,
            current->name ? current->name : "",
            current->author ? current->author : "",
            current->publisher ? current->publisher : "",
            current->year ? (char*)current->year : "",
            current->ISBN ? (char*)current->ISBN : "",
            current->isBorrowed ? "true" : "false",
            current->borrowedBy ? current->borrowedBy : "");

        current = current->next;
        id++;
    }

    fclose(file);
}

// 读取用户文件，返回带头节点的用户链表
userList readUserFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");  // 以只读方式打开文件
    if (file == NULL) {
        return NULL;  // 文件打开失败，返回NULL
    }

    // 创建头节点（哨兵节点）
    userList head = (userList)malloc(sizeof(user));
    if (head == NULL) {
        fclose(file);
        return NULL;
    }
    head->next = NULL;
    userList tail = head;  // 尾指针用于高效追加

    char line[1024];  // 行缓冲区

    // 跳过CSV标题行（如果有）
    fgets(line, sizeof(line), file);

    // 逐行读取数据
    while (fgets(line, sizeof(line), file)) {
        // 创建新节点
        userList newNode = (userList)malloc(sizeof(user));
        if (newNode == NULL) {
            fclose(file);
            return head;  // 返回已读取的部分链表
        }

        // 初始化指针成员
        newNode->name = NULL;
        newNode->username = NULL;
        newNode->password = NULL;
        newNode->next = NULL;

        char* token;
        // 读取用户ID
        token = strtok(line, ",");
        if (token == NULL) continue;
        newNode->id = atoi(trim(token));

        // 读取用户姓名（动态分配内存）
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->name = strdup(trim(token));

        // 读取用户名（动态分配内存）
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->username = strdup(trim(token));

        // 读取密码（动态分配内存）
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->password = strdup(trim(token));

        // 将新节点添加到链表尾部
        tail->next = newNode;
        tail = newNode;
    }

    fclose(file);
    return head;  // 返回带头节点的链表
}
// 将用户链表写入文件
void writeUserFile(const char* fileName, userList head) {
    FILE* file = fopen(fileName, "w");  // 以写入方式打开文件
    if (file == NULL || head == NULL) {
        return;  // 文件打开失败或链表为空，直接返回
    }

    // 写入CSV标题行
    fprintf(file, "ID,Name,Username,Password\n");
    int id = 1;
    // 遍历链表（跳过哨兵节点）
    userList current = head->next;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s\n",
            id,
            current->name ? current->name : "",
            current->username ? current->username : "",
            current->password ? current->password : "");

        current = current->next;
		id++;
    }

    fclose(file);
}