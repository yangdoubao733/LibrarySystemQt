#include "File.h"
#include<stdio.h>


bookList readBookFile(const char* fileName) {//读取文件返回链表头指针
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    bookList head = NULL;
    book* tail = NULL;
    int idCounter = 1;
    char line[512];  // 增大缓冲区以容纳完整行

    while (fgets(line, sizeof(line), file) != NULL) {
        // 移除行尾换行符
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // 忽略空行
        if (line[0] == '\0') continue;

        // 分配新节点
        book* newBook = (book*)malloc(sizeof(book));
        if (!newBook) {
            perror("Memory allocation failed");
            fclose(file);
            return head;
        }

        // 初始化节点
        newBook->id = idCounter++;
        newBook->name = NULL;
        newBook->author = NULL;
        newBook->next = NULL;

        // 使用strtok分割字符串
        char* token = strtok(line, ",");
        if (token == NULL) goto cleanup;  // 格式错误

        // 书名
        newBook->name = strdup(token);
        if (!newBook->name) goto cleanup;

        // 作者
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->author = strdup(token);
        if (!newBook->author) goto cleanup;

        // 出版年份
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->year = atoi(token);

        // ISBN
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->ISBN = atoi(token);

        // 借阅状态
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->isBorrowed = (atoi(token) != 0);

        // 借阅者ID
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newBook->borrowedBy = atoi(token);

        // 添加到链表
        if (head == NULL) {
            head = newBook;
            tail = newBook;
        }
        else {
            tail->next = newBook;
            tail = newBook;
        }

        continue;  // 成功添加，继续下一行

    cleanup:  // 错误处理
        if (newBook->name) free(newBook->name);
        if (newBook->author) free(newBook->author);
        free(newBook);
        idCounter--;  // 回滚ID计数器
    }

    fclose(file);
    return head;
}
void writeBookFile(const char* fileName, bookList head) {//将链表写入文件
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    book* current = head;
    while (current != NULL) {
        // 写入图书信息，格式：书名,作者,出版年份,ISBN,借阅状态,借阅者ID
        // 注意：不写入ID，因为ID在读取时会重新生成
        fprintf(file, "%s,%s,%d,%d,%d,%d\n",
            current->name,
            current->author,
            current->year,
            current->ISBN,
            current->isBorrowed ? 1 : 0,  // 将bool转换为整数
            current->borrowedBy);

        current = current->next;
    }

    fclose(file);

}

userList readUserFile(const char* fileName) {//读取文件返回链表头指针
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening user file");
        return NULL;
    }

    userList head = NULL;
    user* tail = NULL;
    int idCounter = 1;
    char line[256];  // 缓冲区大小

    while (fgets(line, sizeof(line), file) != NULL) {
        // 移除行尾换行符
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // 跳过空行
        if (line[0] == '\0') continue;

        // 分配新用户节点
        user* newUser = (user*)malloc(sizeof(user));
        if (!newUser) {
            perror("Memory allocation failed");
            fclose(file);
            return head;
        }

        // 初始化节点
        newUser->id = idCounter++;
        newUser->name = NULL;
        newUser->username = NULL;
        newUser->password = NULL;
        newUser->next = NULL;

        // 使用strtok分割字符串
        char* token = strtok(line, ",");
        if (token == NULL) goto cleanup;

        // 姓名
        newUser->name = strdup(token);
        if (!newUser->name) goto cleanup;

        // 用户名
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newUser->username = strdup(token);
        if (!newUser->username) goto cleanup;

        // 密码
        token = strtok(NULL, ",");
        if (token == NULL) goto cleanup;
        newUser->password = strdup(token);
        if (!newUser->password) goto cleanup;

        // 添加到链表
        if (head == NULL) {
            head = newUser;
            tail = newUser;
        }
        else {
            tail->next = newUser;
            tail = newUser;
        }

        continue;  // 成功添加，继续下一行

    cleanup:  // 错误处理
        if (newUser->name) free(newUser->name);
        if (newUser->username) free(newUser->username);
        if (newUser->password) free(newUser->password);
        free(newUser);
        idCounter--;  // 回滚ID计数器
    }

    fclose(file);
    return head;

}
void writeUserFile(const char* fileName, userList head) {//将链表写入文件
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening user file for writing");
        return;
    }

    user* current = head;
    while (current != NULL) {
        // 写入用户信息，格式：姓名,用户名,密码
        // 注意：不写入ID，因为ID在读取时会重新生成
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
            // 移除行尾换行符
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            // 跳过空行
            if (line[0] == '\0') continue;

            // 分配新管理员节点
            admin* newAdmin = (admin*)malloc(sizeof(admin));
            if (!newAdmin) {
                perror("Memory allocation failed");
                fclose(file);
                return head;
            }

            // 初始化节点
            newAdmin->username = NULL;
            newAdmin->password = NULL;
            newAdmin->next = NULL;

            // 使用strtok分割字符串
            char* token = strtok(line, ",");
            if (token == NULL) goto cleanup;

            // 用户名
            newAdmin->username = strdup(token);
            if (!newAdmin->username) goto cleanup;

            // 密码
            token = strtok(NULL, ",");
            if (token == NULL) goto cleanup;
            newAdmin->password = strdup(token);
            if (!newAdmin->password) goto cleanup;

            // 添加到链表
            if (head == NULL) {
                head = newAdmin;
                tail = newAdmin;
            }
            else {
                tail->next = newAdmin;
                tail = newAdmin;
            }

            continue;  // 成功添加，继续下一行

        cleanup:  // 错误处理
            if (newAdmin->username) free(newAdmin->username);
            if (newAdmin->password) free(newAdmin->password);
            free(newAdmin);
        }

        fclose(file);
        return head;
    }