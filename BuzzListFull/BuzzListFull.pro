QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Admin/QueueSystem.cpp \
    Admin/adminPageManager.cpp \
    Admin/barworkerqueue.cpp \
    Admin/barworkerscan.cpp \
    Admin/codegenerationpage.cpp \
    Admin/home.cpp \
    User/backend.cpp \
    User/searchbarspage.cpp \
    User/setcrewsizepage.cpp \
    User/userPageManager.cpp \
    User/waitingpage.cpp \
    main.cpp

HEADERS += \
    Admin/QueueSystem.h \
    Admin/adminPageManager.h \
    Admin/barworkerqueue.h \
    Admin/barworkerscan.h \
    Admin/codegenerationpage.h \
    Admin/home.h \
    User/backend.h \
    User/clickablewidget.h \
    User/searchbarspage.h \
    User/setcrewsizepage.h \
    User/userPageManager.h \
    User/waitingpage.h

FORMS +=
# Remove mainwindow.ui since it's not being used anymore

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
