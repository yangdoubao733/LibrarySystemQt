#include "usermainwindow.h"
#include "ui_usermainwindow.h"

UserMainWindow::UserMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ͼ���ݹ���ϵͳ");
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::on_pushButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}

