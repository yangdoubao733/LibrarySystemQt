#include "File.h"
#include<stdio.h>


bookList readBookFile(const char* fileName) {//��ȡ�ļ���������ͷָ��
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    bookList head = NULL;
    book* tail = NULL;
    int idCounter = 1;
    char line[512];  // ���󻺳���������������

    while (fgets(line, sizeof(line), file) != NULL) {
        // �Ƴ���β���з�
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // ���Կ���
        if (line[0] == '\0') continue;

        // �����½ڵ�
        book* newBook = (book*)malloc(sizeof(book));
        if (!newBook) {
            perror("Memory allocation failed");
            fclose(file);
            return head;
        }

        // ��ʼ���ڵ�
        newBook->id = idCounter++;
        newBook->name = NULL;
        newBook->author = NULL;
        newBook->next = NULL;

        // ʹ��strtok�ָ��ַ���
        char* token = strtok(line, ",");
        if (token == NULL) goto cleanup;  // ��ʽ����

        // ����
        newBook->name = strdup(token);
        if (!newBook->name) goto cleanup;

        // ����
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->author = strdup(token);
        if (!newBook->author) goto cleanup;

        // �������
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->year = atoi(token);

        // ISBN
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->ISBN = atoi(token);

        // ����״̬
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->isBorrowed = (atoi(token) != 0);

        // ������ID
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->borrowedBy = atoi(token);

        // ��ӵ�����
        if (head == NULL) {
            head = newBook;
            tail = newBook;
        }
        else {
            tail->next = newBook;
            tail = newBook;
        }

        continue;  // �ɹ���ӣ�������һ��

    cleanup:  // ������
        if (newBook->name) free(newBook->name);
        if (newBook->author) free(newBook->author);
        free(newBook);
        idCounter--;  // �ع�ID������
    }

    fclose(file);
    return head;
}
void writeBookFile(const char* fileName, bookList head) {//������д���ļ�
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    book* current = head;
    while (current != NULL) {
        // д��ͼ����Ϣ����ʽ������,����,�������,ISBN,����״̬,������ID
        // ע�⣺��д��ID����ΪID�ڶ�ȡʱ����������
        fprintf(file, "%s,%s,%d,%d,%d,%d\n",
            current->name,
            current->author,
            current->year,
            current->ISBN,
            current->isBorrowed ? 1 : 0,  // ��boolת��Ϊ����
            current->borrowedBy);

        current = current->next;
    }

    fclose(file);

}

userList readUserFile(const char* fileName) {//��ȡ�ļ���������ͷָ��
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening user file");
        return NULL;
    }

    userList head = NULL;
    user* tail = NULL;
    int idCounter = 1;
    char line[256];  // ��������С

    while (fgets(line, sizeof(line), file) != NULL) {
        // �Ƴ���β���з�
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // ��������
        if (line[0] == '\0') continue;

        // �������û��ڵ�
        user* newUser = (user*)malloc(sizeof(user));
        if (!newUser) {
            perror("Memory allocation failed");
            fclose(file);
            return head;
        }

        // ��ʼ���ڵ�
        newUser->id = idCounter++;
        newUser->name = NULL;
        newUser->username = NULL;
        newUser->password = NULL;
        newUser->next = NULL;

        // ʹ��strtok�ָ��ַ���
        char* token = strtok(line, ",");
        if (token == NULL) goto cleanup;

        // ����
        newUser->name = strdup(token);
        if (!newUser->name) goto cleanup;

        // �û���
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newUser->username = strdup(token);
        if (!newUser->username) goto cleanup;

        // ����
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newUser->password = strdup(token);
        if (!newUser->password) goto cleanup;

        // ��ӵ�����
        if (head == NULL) {
            head = newUser;
            tail = newUser;
        }
        else {
            tail->next = newUser;
            tail = newUser;
        }

        continue;  // �ɹ���ӣ�������һ��

    cleanup:  // ������
        if (newUser->name) free(newUser->name);
        if (newUser->username) free(newUser->username);
        if (newUser->password) free(newUser->password);
        free(newUser);
        idCounter--;  // �ع�ID������
    }

    fclose(file);
    return head;

}
void writeUserFile(const char* fileName, userList head) {//������д���ļ�
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening user file for writing");
        return;
    }

    user* current = head;
    while (current != NULL) {
        // д���û���Ϣ����ʽ������,�û���,����
        // ע�⣺��д��ID����ΪID�ڶ�ȡʱ����������
        fprintf(file, "%s,%s,%s\n",
            current->name,
            current->username,
            current->password);

        current = current->next;
    }


    adminList readAdminFile(const char* fileName) {
        FILE* file = fopen(fileName, "r");
        if (file == NULL) {
            perror("Error opening admin file");
            return NULL;
        }

        adminList head = NULL;
        admin* tail = NULL;
        char line[256];

        while (fgets(line, sizeof(line), file) != NULL) {
            // �Ƴ���β���з�
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            // ��������
            if (line[0] == '\0') continue;

            // �����¹���Ա�ڵ�
            admin* newAdmin = (admin*)malloc(sizeof(admin));
            if (!newAdmin) {
                perror("Memory allocation failed");
                fclose(file);
                return head;
            }

            // ��ʼ���ڵ�
            newAdmin->username = NULL;
            newAdmin->password = NULL;
            newAdmin->next = NULL;

            // ʹ��strtok�ָ��ַ���
            char* token = strtok(line, ",");
            if (token == NULL) goto cleanup;

            // �û���
            newAdmin->username = strdup(token);
            if (!newAdmin->username) goto cleanup;

            // ����
            token = strtok(NULL, ",");
            if (token == NULL) goto cleanup;
            newAdmin->password = strdup(token);
            if (!newAdmin->password) goto cleanup;

            // ��ӵ�����
            if (head == NULL) {
                head = newAdmin;
                tail = newAdmin;
            }
            else {
                tail->next = newAdmin;
                tail = newAdmin;
            }

            continue;  // �ɹ���ӣ�������һ��

        cleanup:  // ������
            if (newAdmin->username) free(newAdmin->username);
            if (newAdmin->password) free(newAdmin->password);
            free(newAdmin);
        }

        fclose(file);
        return head;
    }