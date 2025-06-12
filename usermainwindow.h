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

private:
    Ui::UserMainWindow *ui;
};

#endif // USERMAINWINDOW_H
