#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QWidget>

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
    ~AdminMainWindow();

private slots:


    void on_bookManage_2_clicked();

    void on_userManage_2_clicked();

    void on_exitButton_2_clicked();

    void on_userManage_clicked();

    void on_exitButton_clicked();

    void on_searchBookButton_clicked();

    void on_addBookButton_clicked();

    void on_deleteBookButton_clicked();

    void on_bookManage_3_clicked();

    void on_exitButton_3_clicked();

    void on_searchUserButton_clicked();

    void on_addUserButton_clicked();

    void on_deleteUserButton_clicked();

private:
    Ui::AdminMainWindow *ui;
};

#endif // ADMINMAINWINDOW_H
