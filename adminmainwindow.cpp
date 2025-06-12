#include <qlist.h>
#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include "Book.h"
#include "File.h"
#include <qstandarditemmodel.h>
#include <QMessageBox>

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("图书馆管理系统");
	//初始化显示所有图书
    ui->bookTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可修改
    //读取文件
    bookList bl;
    bl = readBookFile(BOOKPATH);
    book* book = bl->next;
    QString current_bookName = ui->bookName->text();
    QString current_ISBN = ui->ISBN->text();
    QString current_autho = ui->Author->text();
    QString current_year = ui->Year->text();
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
    ui->bookTableView->setModel(model);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}


//主页面跳转图书管理
void AdminMainWindow::on_bookManage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//主页面跳转用户管理
void AdminMainWindow::on_userManage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//主页面退出
void AdminMainWindow::on_exitButton_2_clicked()
{
    this->close();
}

//图书页面跳转用户页面
void AdminMainWindow::on_userManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//图书页面退出
void AdminMainWindow::on_exitButton_clicked()
{
    this->close();
}

//图书页面 查找图书
void AdminMainWindow::on_searchBookButton_clicked()
{
    //读取文件
    bookList bl;
    bl = readBookFile(BOOKPATH);
    QString current_bookName = ui->bookName->text();
    QString current_ISBN = ui->ISBN->text();
    QString current_author = ui->Author->text();
    QString current_year = ui->Year->text();

	//查找图书
	bookList foundBook;
	book toSearchBook;

    if (current_bookName.isEmpty() && current_ISBN.isEmpty() && current_author.isEmpty() && current_year.isEmpty()) {
        foundBook = bl->next; //如果没有输入任何条件，则显示所有图书
    }
    else {
        
        toSearchBook.name = current_bookName.toUtf8().data();
		toSearchBook.ISBN = current_ISBN.toInt();
		toSearchBook.author = current_author.toUtf8().data();
		toSearchBook.year = current_year.toInt();
		//第一次搜索 - 按书名、ISBN、作者、年份依次搜索
        if (!current_bookName.isEmpty()) {
            int i = 0;
            SearchBook(toSearchBook, bl, 'n', foundBook, i);
		}
        if (!current_ISBN.isEmpty() && !foundBook) {
            int i = 0;
			SearchBook(toSearchBook, bl, 'i', foundBook, i);
            }
        if (!current_author.isEmpty() && !foundBook) {
            int i = 0;
            SearchBook(toSearchBook, bl, 'a', foundBook, i);
        }
        if (!current_year.isEmpty() && !foundBook) {
            int i = 0;
            SearchBook(toSearchBook, bl, 'y', foundBook, i);
        }
        // 二次搜索 - 在已找到的结果中继续筛选
         
        // 按ISBN再次筛选
        if (!current_ISBN.isEmpty() && foundBook) {
            int i = 0;
            bookList tempList = foundBook;
            foundBook = NULL;
            SearchBook(toSearchBook, tempList, 'i', foundBook, i);
        }

        // 按作者再次筛选
        if (!current_author.isEmpty() && foundBook ) {
            int i = 0;
            bookList tempList = foundBook;
            foundBook = NULL;
            SearchBook(toSearchBook, tempList, 'a', foundBook, i);
        }

        // 按年份再次筛选
        if (!current_year.isEmpty() && foundBook) {
            int i = 0;
            bookList tempList = foundBook;
            foundBook = NULL;
            SearchBook(toSearchBook, tempList, 'y', foundBook, i);
        }

        if (!foundBook) {
            QMessageBox::information(this, "提示", "未找到相关图书！", QMessageBox::Ok);
            return;
        }
    }
    
    //设置标题
    QStandardItemModel* model = new QStandardItemModel(0, 5, this);
    model->setHorizontalHeaderLabels({ "id", "书名", "作者" ,"ISBN", "出版日期" });//设置表头
    QList<QStandardItem*> rowItems;
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
    ui->bookTableView->setModel(model);
}

//图书页面 添加图书
void AdminMainWindow::on_addBookButton_clicked()
{

}

//图书页面 删除图书
void AdminMainWindow::on_deleteBookButton_clicked()
{

}

//用户页面跳转图书页面
void AdminMainWindow::on_bookManage_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

//用户页面退出
void AdminMainWindow::on_exitButton_3_clicked()
{
    this->close();
}

//用户页面 查找用户
void AdminMainWindow::on_searchUserButton_clicked()
{

}

//用户页面 添加用户
void AdminMainWindow::on_addUserButton_clicked()
{

}

//用户页面 删除用户
void AdminMainWindow::on_deleteUserButton_clicked()
{

}

