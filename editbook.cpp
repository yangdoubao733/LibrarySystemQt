#include "editbook.h"
#include "ui_editbook.h"

EditBook::EditBook(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditBook)
{
    ui->setupUi(this);
    setWindowTitle("ͼ��ݹ���ϵͳ");
}

EditBook::~EditBook()
{
    delete ui;
}
