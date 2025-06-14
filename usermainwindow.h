#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H
#include <QWidget>

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = nullptr);
    ~UserMainWindow();

private slots:
    void on_BorrowManage_2_clicked();

    void on_ReturnManage_2_clicked();

    void on_exitButton_3_clicked();

    void on_ReturnManage_clicked();

    void on_exitButton_clicked();

    void on_borrowBookButton_clicked();

    void on_BookManage_2_clicked();

    void on_exitButton_2_clicked();

    void on_searchButton_clicked();

    void on_returnButton_clicked();

    void on_searchBookButton_clicked();




private:
    Ui::UserMainWindow *ui;
};

#endif // USERMAINWINDOW_H
