#include "editbook.h"
#include "ui_editbook.h"

EditBook::EditBook(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditBook)
{
    ui->setupUi(this);
    setWindowTitle("图书馆管理系统");
}

EditBook::~EditBook()
{
    delete ui;
}
