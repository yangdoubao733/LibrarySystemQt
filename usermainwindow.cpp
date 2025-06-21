#include <qlist.h>
#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include "Book.h"
#include "File.h"
#include "User.h"
#include <qstandarditemmodel.h>
#include <QMessageBox>
#include <QModelIndex>
#include <string.h>
#include <login.h>

extern QString login_UserName;

UserMainWindow::UserMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("图书馆管理系统");
    //初始化显示所有图书
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可修改
    //读取文件
    bookList bl;
    bl = readBookFile(BOOKPATH);
    book* book = bl->next;
    QString current_bookName = ui->bookName->text();
    QString current_autho = ui->Author->text();
    //设置标题
    QStandardItemModel* model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({ "id", "书名", "作者" ,"ISBN", "出版日期" });//设置表头
    QList<QStandardItem*> rowItems;
    while (book) {//遍历链表
        rowItems.clear();
        rowItems.append(new QStandardItem(QString::number(book->id)));
        rowItems.append(new QStandardItem(QString::fromUtf8(book->name)));
        rowItems.append(new QStandardItem(QString::fromUtf8(book->author)));
        rowItems.append(new QStandardItem(QString::number(book->ISBN)));
        rowItems.append(new QStandardItem(QString::number(book->year)));
        model->appendRow(rowItems);
        book = book->next;
    }
    ui->tableView->setModel(model);
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

//主页面跳转借阅页面
void UserMainWindow::on_BorrowManage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//主页面跳转归还页面
void UserMainWindow::on_ReturnManage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//主页面退出
void UserMainWindow::on_exitButton_3_clicked()
{
    this->close();
}

//借阅页面跳转归还页面
void UserMainWindow::on_ReturnManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//借阅页面退出
void UserMainWindow::on_exitButton_clicked()
{
    this->close();
}

//借阅页面 查找图书
void UserMainWindow::on_searchBookButton_clicked()
{
    //读取文件
    bookList bl;
    bl = readBookFile(BOOKPATH);
    QString current_bookName = ui->bookName->text();
    QString current_author = ui->Author->text();

    //查找图书
    bookList foundBook= new book;
	foundBook->next = NULL; // 初始化链表
    book *toSearchBook = new book;

    if (current_bookName.isEmpty() && current_author.isEmpty()) {
        foundBook = bl->next; //如果没有输入任何条件，则显示所有图书
    }
    else {
        toSearchBook->name = current_bookName.toUtf8().data();
        toSearchBook->author = current_author.toUtf8().data();
        //第一次搜索 - 按书名、作者依次搜索
        if (!current_bookName.isEmpty()) {
            int i = 0;
            SearchBook(*toSearchBook, bl, 'n', foundBook, i);
        }
        if (!current_author.isEmpty() && !foundBook) {
            int i = 0;
            SearchBook(*toSearchBook, bl, 'a', foundBook, i);
        }
        // 二次搜索 - 在已找到的结果中继续筛选
        // 按年份再次筛选
        if (!current_author.isEmpty() && foundBook ) {
            int i = 0;
            bookList tempList = foundBook;
            foundBook = NULL;
            SearchBook(*toSearchBook, tempList, 'a', foundBook, i);
        }

        if (!foundBook->next) {
            QMessageBox::information(this, "提示", "未找到相关图书！", QMessageBox::Ok);
            return;
        }
    }

    //设置标题
    QStandardItemModel* model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({ "id", "书名", "作者" ,"ISBN", "出版日期" });//设置表头
    QList<QStandardItem*> rowItems;
	foundBook = foundBook->next; //跳过头节点
    while (foundBook) {//遍历链表
        rowItems.clear();
        rowItems.append(new QStandardItem(QString::number(foundBook->id)));
        rowItems.append(new QStandardItem(QString::fromUtf8(foundBook->name)));
        rowItems.append(new QStandardItem(QString::fromUtf8(foundBook->author)));
        rowItems.append(new QStandardItem(QString::number(foundBook->ISBN)));
        rowItems.append(new QStandardItem(QString::number(foundBook->year)));
        model->appendRow(rowItems);
        foundBook = foundBook->next;
    }
    ui->tableView->setModel(model);
}

//借阅页面 借阅图书
void UserMainWindow::on_borrowBookButton_clicked()
{
    // 获取当前选中的图书
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要借阅的图书！");
        return;
    }

    // 获取图书ID（假设第一列是ID）
    int bookId = selected.at(0).data().toInt();

    // 读取图书文件
    bookList bl = readBookFile(BOOKPATH);
    if (!bl) {
        QMessageBox::warning(this, "警告", "无法读取图书数据！");
        return;
    }

    // 查找图书
    book *tempBook = new book;
    tempBook->id = bookId;
    bookList foundBook = new book(); // 创建头节点
    foundBook->next = nullptr;
    int i = 0;
    if (!SearchBook(*tempBook, bl, 'i', foundBook, i)) {
        QMessageBox::warning(this, "警告", "未找到该图书！");
        delete foundBook;
        return;
    }

    // 检查图书是否已被借阅
    book* actualBook = foundBook->next;
    if (actualBook->isBorrowed) {
        QMessageBox::warning(this, "警告", "该图书已被借出！");
        delete foundBook;
        return;
    }

    // 使用全局变量 login_UserName 作为借阅者
    if (BorrowBook(*actualBook, bl, login_UserName.toUtf8().data())) {
        // 更新文件
        writeBookFile(BOOKPATH, bl);
        QMessageBox::information(this, "提示", "借阅成功！");
        // 刷新列表
        on_searchBookButton_clicked();
    }
    else {
        QMessageBox::warning(this, "警告", "借阅失败！");
    }

    delete foundBook; // 释放内存
}

//归还页面跳转借阅页面
void UserMainWindow::on_BookManage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

//归还页面退出
void UserMainWindow::on_exitButton_2_clicked()
{
    this->close();
}

//归还页面 查找图书
void UserMainWindow::on_searchButton_clicked()
{
    // 读取文件
    bookList bl = readBookFile(BOOKPATH);
    if (!bl) {
        QMessageBox::warning(this, "警告", "无法读取图书数据！");
        return;
    }

    QString current_bookName = ui->bookName_2->text();
    QString current_author = ui->lineEdit_6->text();

    // 查找图书
    bookList foundBook = new book(); // 创建头节点
    foundBook->next = nullptr;
    book* current = foundBook;

    book* p = bl->next;
    while (p) {
        bool nameMatch = current_bookName.isEmpty() ||
            (QString::fromUtf8(p->name).contains(current_bookName));
        bool authorMatch = current_author.isEmpty() ||
            (QString::fromUtf8(p->author).contains(current_author));

        // 只显示当前用户借阅的图书
        if (p->isBorrowed && strcmp(p->borrowedBy, login_UserName.toUtf8().data()) == 0 &&
            (nameMatch || authorMatch)) {
            current->next = new book(*p);
            current = current->next;
            current->next = nullptr;
        }
        p = p->next;
    }

    if (!foundBook->next) {
        QMessageBox::information(this, "提示", "未找到相关已借阅图书！");
        delete foundBook;
        return;
    }

    // 设置表格模型
    QStandardItemModel* model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({ "id", "书名", "作者", "ISBN", "出版日期" });

    book* displayBook = foundBook->next;
    QList<QStandardItem*> rowItems;
    while (displayBook) {
		rowItems.clear();
        rowItems.append(new QStandardItem(QString::number(displayBook->id)));
        rowItems.append(new QStandardItem(QString::fromUtf8(displayBook->name)));
        rowItems.append(new QStandardItem(QString::fromUtf8(displayBook->author)));
        rowItems.append(new QStandardItem(QString::number(displayBook->ISBN)));
        rowItems.append(new QStandardItem(QString::number(displayBook->year)));
        model->appendRow(rowItems);
        displayBook = displayBook->next;
    }

    ui->tableView_2->setModel(model);
    delete foundBook; // 释放内存
}

//归还页面 归还图书
void UserMainWindow::on_returnButton_clicked()
{
    // 获取当前选中的图书
    QModelIndexList selected = ui->tableView_2->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要归还的图书！");
        return;
    }

    // 获取图书ID（假设第一列是ID）
    int bookId = selected.at(0).data().toInt();

    // 读取图书文件
    bookList bl = readBookFile(BOOKPATH);
    if (!bl) {
        QMessageBox::warning(this, "警告", "无法读取图书数据！");
        return;
    }

    // 查找并归还图书
    book* p = bl->next;
    while (p) {
        if (p->id == bookId && p->isBorrowed && p->borrowedBy &&
            QString::fromUtf8(p->borrowedBy) == login_UserName) {
            // 归还图书
            p->isBorrowed = false;
            delete[] p->borrowedBy; // 释放原内存
            p->borrowedBy = nullptr; // 设置为未借阅状态

            // 更新文件
            writeBookFile(BOOKPATH, bl);
            QMessageBox::information(this, "提示", "归还成功！");

            // 刷新列表
            on_searchButton_clicked();
            return;
        }
        p = p->next;
    }

    QMessageBox::warning(this, "警告", "未找到该图书或您没有借阅此图书！");
}
