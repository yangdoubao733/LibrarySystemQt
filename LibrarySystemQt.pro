QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmainwindow.cpp \
    editbook.cpp \
    login.cpp \
    main.cpp \
    usermainwindow.cpp

HEADERS += \
    adminmainwindow.h \
    editbook.h \
    login.h \
    usermainwindow.h

FORMS += \
    adminmainwindow.ui \
    editbook.ui \
    login.ui \
    usermainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
