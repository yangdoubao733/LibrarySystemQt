#include "login.h"
#include "adminmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}
