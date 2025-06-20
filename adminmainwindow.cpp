#include <qlist.h>
#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include "Book.h"
#include "File.h"
#include <qstandarditemmodel.h>
#include <QMessageBox>
#include "Linklist.h"

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
    if (!bl) {
        QMessageBox::warning(this, "警告", "无法读取图书数据！");
        return;
	}
    book* book = bl->next;
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
	QMessageBox::information(this, "提示", "欢迎使用图书馆管理系统！", QMessageBox::Ok);
	DeleteBookLinkList(bl); //释放链表内存
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
    if (!bl) {
        QMessageBox::warning(this, "警告", "无法读取图书数据！");
        return;
	}
    QString current_bookName = ui->bookName->text();
    QString current_ISBN = ui->ISBN->text();
    QString current_author = ui->Author->text();
    QString current_year = ui->Year->text();

	//查找图书
	bookList foundBook;
	book *toSearchBook = new book;
    //初始化链表
    foundBook = (bookList)new book;
    if (foundBook == NULL) {
        return;
    }
    foundBook->next = NULL;
    if (current_bookName.isEmpty() && current_ISBN.isEmpty() && current_author.isEmpty() && current_year.isEmpty()) {
        foundBook = bl; //如果没有输入任何条件，则显示所有图书
    }
    else {
        
        toSearchBook->name = strdup(current_bookName.toUtf8().data());
        toSearchBook->ISBN = current_ISBN.toInt();
        toSearchBook->author = strdup(current_author.toUtf8().data());
        toSearchBook->year = current_year.toInt();
		//第一次搜索 - 按书名、ISBN、作者、年份依次搜索
        if (!current_bookName.isEmpty()) {
            int i = 0;
            SearchBook(*toSearchBook, bl, 'n', foundBook, i);
		}
        if (!current_ISBN.isEmpty() && !foundBook->next) {
            int i = 0;
			SearchBook(*toSearchBook, bl, 'i', foundBook, i);
            }
        if (!current_author.isEmpty() && !foundBook->next) {
            int i = 0;
            SearchBook(*toSearchBook, bl, 'a', foundBook, i);
        }
        if (!current_year.isEmpty() && !foundBook->next) {
            int i = 0;
            SearchBook(*toSearchBook, bl, 'y', foundBook, i);
        }
        // 二次搜索 - 在已找到的结果中继续筛选
         
        // 按ISBN再次筛选
        if (!current_ISBN.isEmpty() && foundBook->next) {
            int i = 0;
            bookList tempList = foundBook;
            foundBook = (bookList)new book;
            if (foundBook == NULL) {
                return;
            }
            foundBook->next = NULL;
            SearchBook(*toSearchBook, tempList, 'i', foundBook, i);
        }

        // 按作者再次筛选
        if (!current_author.isEmpty() && foundBook->next ) {
            int i = 0;
            bookList tempList = foundBook;
            foundBook = (bookList)new book;
            if (foundBook == NULL) {
                return;
            }
            foundBook->next = NULL;
            SearchBook(*toSearchBook, tempList, 'a', foundBook, i);
        }

        // 按年份再次筛选
        if (!current_year.isEmpty() && foundBook->next) {
            int i = 0;
            bookList tempList = foundBook;
            foundBook = (bookList)new book;
            if (foundBook == NULL) {
                return;
            }
            foundBook->next = NULL;
            SearchBook(*toSearchBook, tempList, 'y', foundBook, i);
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
    bookList p = foundBook->next;
    while (p) {//遍历链表
        rowItems.clear();
        rowItems.append(new QStandardItem(QString::number(p->id)));
		QMessageBox::warning(this, "调试", QString::fromUtf8(p->name), QMessageBox::Ok);
        rowItems.append(new QStandardItem(QString::fromUtf8(p->name)));
		QMessageBox::warning(this, "调试", QString::fromUtf8(p->author), QMessageBox::Ok);
        rowItems.append(new QStandardItem(QString::fromUtf8(p->author)));
		QMessageBox::warning(this, "调试", QString::number(p->ISBN), QMessageBox::Ok);
        rowItems.append(new QStandardItem(QString::number(p->ISBdrN)));
		QMessageBox::warning(this, "调试", QString::number(p->year), QMessageBox::Ok);
        rowItems.append(new QStandardItem(QString::number(p->year)));
        model->appendRow(rowItems);
        p = p->next;
    }
    ui->bookTableView->setModel(model);
	DeleteBookLinkList(foundBook); //释放链表内存
	DeleteBookLinkList(bl); //释放链表内存
}

//图书页面 添加图书
void AdminMainWindow::on_addBookButton_clicked()
{
    book *addedBook = new book;
	addedBook->name = strdup(ui->bookName->text().toUtf8().data());
	addedBook->ISBN = ui->ISBN->text().toInt();
	addedBook->author = strdup(ui->Author->text().toUtf8().data());
	addedBook->year = ui->Year->text().toInt();
    addedBook->publisher = strdup("");
    QMessageBox::warning(this, "调试", ui->bookName->text(), QMessageBox::Ok);
    QMessageBox::warning(this, "调试", ui->ISBN->text(), QMessageBox::Ok);
    QMessageBox::warning(this, "调试", ui->Author->text(), QMessageBox::Ok);
    QMessageBox::warning(this, "调试", ui->Year->text(), QMessageBox::Ok);

    if (ui->bookName->text().isEmpty() || ui->ISBN->text().isEmpty() || ui->Author->text().isEmpty() || ui->Year->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "有信息未填写！", QMessageBox::Ok);
        return;
    }
	bookList bl;
    bl = readBookFile(BOOKPATH);
    if (bl == NULL) {
		QMessageBox::warning(this, "错误", "无法读取图书文件！", QMessageBox::Ok);
        return;
    }
    
    if (!AddBook(*addedBook, bl)) {
        QMessageBox::warning(this, "错误", "图书添加失败！", QMessageBox::Ok);
        return;
    }
    
	writeBookFile(BOOKPATH, bl); //写入文件
	DeleteBookLinkList(bl); //释放链表内存
    ui->bookName->clear();
	ui->ISBN->clear();
	ui->Author->clear();
	ui->Year->clear();
	QMessageBox::information(this, "提示", "图书添加成功！", QMessageBox::Ok);
    
}

//图书页面 删除图书
void AdminMainWindow::on_deleteBookButton_clicked()
{

    QList<QModelIndex> list = ui->bookTableView->selectionModel()->selectedIndexes();
    if(list.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先选择要删除的图书！", QMessageBox::Ok);
        return;
	}

	book *deletedBook = new book;
	deletedBook->id = list[0].data().toInt(); //获取选中图书的id
	deletedBook->name = strdup(list[1].data().toString().toUtf8().data());
    deletedBook->author = strdup(list[2].data().toString().toUtf8().data());
	deletedBook->ISBN = list[3].data().toInt();
	deletedBook->year = list[4].data().toInt();
    bookList bl;
    bl = readBookFile(BOOKPATH);
    if (bl == NULL) {
        QMessageBox::warning(this, "错误", "无法读取图书文件！", QMessageBox::Ok);
        return;
    }
    if (!DeleteBook(*deletedBook, bl)) {
        QMessageBox::warning(this, "错误", "图书删除失败！", QMessageBox::Ok);
        return;
    }
    writeBookFile(BOOKPATH, bl); //写入文件
    DeleteBookLinkList(bl); //释放链表内存
    ui->bookName->clear();
    ui->ISBN->clear();
    ui->Author->clear();
    ui->Year->clear();
	QMessageBox::information(this, "提示", "图书删除成功！", QMessageBox::Ok);
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
    //读取文件
	userList ul = readUserFile(USERPATH);
    if (ul == NULL) {
        QMessageBox::warning(this, "错误", "无法读取用户文件！", QMessageBox::Ok);
        return;
	}
	QString current_userName = ui->userName->text();
	QString current_name = ui->name->text();
	QString current_password = ui->password->text();

    //查找图书
    userList foundUser;
    User *toSearchUser = new User;
    //初始化链表
    foundUser = (userList)new User;
    if (foundUser == NULL) {
        return;
    }
    foundUser->next = NULL;
    if (current_name.isEmpty() && current_password.isEmpty() && current_password.isEmpty()) {
        foundUser = ul; //如果没有输入任何条件，则显示所有图书
    }
    else {

		toSearchUser->name = strdup(current_name.toUtf8().data());
		toSearchUser->username = strdup(current_userName.toUtf8().data());
		toSearchUser->password = strdup(current_password.toUtf8().data());
        //第一次搜索 - 按用户名、账号、密码依次搜索
        if (!current_userName.isEmpty()) {
            int i = 0;
            SearchUser(*toSearchUser, ul, 'u', foundUser, i);
		}
        if (!current_name.isEmpty() && !foundUser->next) {
			int i = 0;
            SearchUser(*toSearchUser, ul, 'n', foundUser, i);
		}
        if (!current_password.isEmpty() && !foundUser->next) {
            int i = 0;
            SearchUser(*toSearchUser, ul, 'p', foundUser, i);
		}
        // 二次搜索 - 在已找到的结果中继续筛选
        
        // 按姓名再次筛选
        if (!current_name.isEmpty() && foundUser->next) {
            int i = 0;
            userList tempList = foundUser;
            foundUser = (userList)new User;
            if (foundUser == NULL) {
                return;
            }
            foundUser->next = NULL;
            SearchUser(*toSearchUser, tempList, 'n', foundUser, i);
			DeleteUserLinkList(tempList); //释放临时链表内存
        }

        // 按密码再次筛选
        if (!current_password.isEmpty() && foundUser->next) {
            int i = 0;
            userList tempList = foundUser;
            foundUser = (userList)new User;
            if (foundUser == NULL) {
                return;
            }
            foundUser->next = NULL;
            SearchUser(*toSearchUser, tempList, 'p', foundUser, i);
			DeleteUserLinkList(tempList); //释放临时链表内存
        }

        if (!foundUser->next) {
            QMessageBox::information(this, "提示", "未找到相关用户！", QMessageBox::Ok);
            DeleteUserLinkList(foundUser);
            DeleteUserLinkList(ul);
            return;
        }
    }

    //设置标题
    QStandardItemModel* model = new QStandardItemModel(0, 4, this);
    model->setHorizontalHeaderLabels({ "id", "用户名", "账号" ,"密码"});//设置表头
    QList<QStandardItem*> rowItems;
	foundUser = foundUser->next; //跳过头节点
    while (foundUser) {//遍历链表
        rowItems.clear();
		rowItems.append(new QStandardItem(QString::number(foundUser->id)));
		rowItems.append(new QStandardItem(QString::fromUtf8(foundUser->username)));
		rowItems.append(new QStandardItem(QString::fromUtf8(foundUser->name)));
		rowItems.append(new QStandardItem(QString::fromUtf8(foundUser->password)));
        model->appendRow(rowItems);
        foundUser = foundUser->next;
    }
    ui->userTableView->setModel(model);
    DeleteUserLinkList(foundUser); //释放链表内存
    DeleteUserLinkList(ul); //释放链表内存

}

//用户页面 添加用户
void AdminMainWindow::on_addUserButton_clicked()
{
    user *addedUser = new user;
	addedUser->username = strdup(ui->userName->text().toUtf8().data());
	addedUser->name = strdup(ui->name->text().toUtf8().data());
	addedUser->password = strdup(ui->password->text().toUtf8().data());

    userList ul;
    ul = readUserFile(BOOKPATH);
    if (ul == NULL) {
        QMessageBox::warning(this, "错误", "无法读取用户文件！", QMessageBox::Ok);
        return;
    }
    if (!AddUser(*addedUser, ul)) {
        QMessageBox::warning(this, "错误", "用户添加失败！", QMessageBox::Ok);
        return;
    }
    writeUserFile(USERPATH, ul); //写入文件
    DeleteUserLinkList(ul); //释放链表内存
    ui->userName->clear();
    ui->name->clear();
    ui->password->clear();
}

//用户页面 删除用户
void AdminMainWindow::on_deleteUserButton_clicked()
{
    QList<QModelIndex> list = ui->userTableView->selectionModel()->selectedIndexes();
    if (!list.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先选择要删除的用户！", QMessageBox::Ok);
        return;
    }

    user *deletedUser = new user;
	deletedUser->id = list[0].data().toInt(); //获取选中用户的id
	deletedUser->username = strdup(list[1].data().toString().toUtf8().data());
	deletedUser->name = strdup(list[2].data().toString().toUtf8().data());
	deletedUser->password = strdup(list[3].data().toString().toUtf8().data());
    userList ul;
    ul = readUserFile(USERPATH);
    if (ul == NULL) {
        QMessageBox::warning(this, "错误", "无法读取用户文件！", QMessageBox::Ok);
        return;
    }
    if (!DeleteUser(*deletedUser, ul)) {
        QMessageBox::warning(this, "错误", "用户删除失败！", QMessageBox::Ok);
        return;
    }
    writeUserFile(USERPATH, ul); //写入文件
    DeleteUserLinkList(ul); //释放链表内存
    ui->userName->clear();
    ui->name->clear();
    ui->password->clear();
}

