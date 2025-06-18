#include "File.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����������ȥ���ַ�����β�Ŀհ��ַ�
char* trim(char* str) {
    char* end;
    // ȥ����ͷ�հ��ַ�
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')) {
        str++;
    }
    if (*str == 0) {  // ȫ���ǿհ��ַ������
        return str;
    }
    // ȥ��ĩβ�հ��ַ�
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        end--;
    }
    *(end + 1) = '\0';  // ��ĩβ����ַ���������
    return str;
}


// ��ȡͼ���ļ�������ͼ������ͷָ��
bookList readBookFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");  // ��ֻ����ʽ���ļ�
    if (file == NULL) {
        return NULL;  // �ļ���ʧ�ܣ����ؿ�ָ��
    }

    // ����ͷ�ڵ㣨�ڱ��ڵ㣩
    bookList head = (bookList)malloc(sizeof(book));
    if (head == NULL) {
        fclose(file);
        return NULL;
    }
    head->next = NULL;
    bookList tail = head;  // βָ�����ڸ�Ч׷��

    char line[1024];  // �л�����

    // ����CSV�����У�����У�
    fgets(line, sizeof(line), file);

    // ���ж�ȡ����
    while (fgets(line, sizeof(line), file)) {
        // �����½ڵ�
        bookList newNode = (bookList)malloc(sizeof(book));
        if (newNode == NULL) {
            fclose(file);
            return head;  // �����Ѷ�ȡ�Ĳ�������
        }

        // ��ʼ��ָ���Ա
        newNode->name = NULL;
        newNode->author = NULL;
        newNode->publisher = NULL;
        newNode->borrowedBy = NULL;
        newNode->next = NULL;

        char* token;
        // ��ȡͼ��ID
        token = strtok(line, ",");
        if (token == NULL) continue;
        newNode->id = atoi(trim(token));

        // ��ȡͼ�����ƣ���̬�����ڴ棩
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->name = strdup(trim(token));

        // ��ȡ���ߣ���̬�����ڴ棩
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->author = strdup(trim(token));

        // ��ȡ�����磨��̬�����ڴ棩
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->publisher = strdup(trim(token));

        // ��ȡ�������
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->year = atoi(trim(token));

        // ��ȡISBN
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->ISBN = atoi(trim(token));

        // ��ȡ����״̬
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->isBorrowed = (strcmp(trim(token), "true") == 0);

        // ��ȡ�����ߣ���̬�����ڴ棩
        token = strtok(NULL, ",");
        if (token != NULL) {
            newNode->borrowedBy = strdup(trim(token));
        }
        else {
            newNode->borrowedBy = NULL;
        }

        // ���½ڵ���ӵ�����β��
        tail->next = newNode;
        tail = newNode;
    }

    fclose(file);
    return head;  // ���ش�ͷ�ڵ������
}

// ��ͼ������д���ļ�
void writeBookFile(const char* fileName, bookList head) {
    FILE* file = fopen(fileName, "w");  // ��д�뷽ʽ���ļ�
    if (file == NULL || head == NULL) {
        return;  // �ļ���ʧ�ܻ�����Ϊ�գ�ֱ�ӷ���
    }

    // д��CSV������
    fprintf(file, "ID,Name,Author,Publisher,Year,ISBN,IsBorrowed,BorrowedBy\n");
	int id = 1;  // ��1��ʼ����ID
    // �������������ڱ��ڵ㣩
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

// ��ȡ�û��ļ������ش�ͷ�ڵ���û�����
userList readUserFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");  // ��ֻ����ʽ���ļ�
    if (file == NULL) {
        return NULL;  // �ļ���ʧ�ܣ�����NULL
    }

    // ����ͷ�ڵ㣨�ڱ��ڵ㣩
    userList head = (userList)malloc(sizeof(user));
    if (head == NULL) {
        fclose(file);
        return NULL;
    }
    head->next = NULL;
    userList tail = head;  // βָ�����ڸ�Ч׷��

    char line[1024];  // �л�����

    // ����CSV�����У�����У�
    fgets(line, sizeof(line), file);

    // ���ж�ȡ����
    while (fgets(line, sizeof(line), file)) {
        // �����½ڵ�
        userList newNode = (userList)malloc(sizeof(user));
        if (newNode == NULL) {
            fclose(file);
            return head;  // �����Ѷ�ȡ�Ĳ�������
        }

        // ��ʼ��ָ���Ա
        newNode->name = NULL;
        newNode->username = NULL;
        newNode->password = NULL;
        newNode->next = NULL;

        char* token;
        // ��ȡ�û�ID
        token = strtok(line, ",");
        if (token == NULL) continue;
        newNode->id = atoi(trim(token));

        // ��ȡ�û���������̬�����ڴ棩
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->name = strdup(trim(token));

        // ��ȡ�û�������̬�����ڴ棩
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->username = strdup(trim(token));

        // ��ȡ���루��̬�����ڴ棩
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newNode->password = strdup(trim(token));

        // ���½ڵ���ӵ�����β��
        tail->next = newNode;
        tail = newNode;
    }

    fclose(file);
    return head;  // ���ش�ͷ�ڵ������
}
// ���û�����д���ļ�
void writeUserFile(const char* fileName, userList head) {
    FILE* file = fopen(fileName, "w");  // ��д�뷽ʽ���ļ�
    if (file == NULL || head == NULL) {
        return;  // �ļ���ʧ�ܻ�����Ϊ�գ�ֱ�ӷ���
    }

    // д��CSV������
    fprintf(file, "ID,Name,Username,Password\n");
    int id = 1;
    // �������������ڱ��ڵ㣩
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