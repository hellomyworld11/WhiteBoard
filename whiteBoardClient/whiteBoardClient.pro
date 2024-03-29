QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cboardoper.cpp \
    cboardview.cpp \
    ccircleitem.cpp \
    ceraseitem.cpp \
    citembase.cpp \
    clineitem.cpp \
    colorsel.cpp \
    cpathlineitem.cpp \
    crectitem.cpp \
    ctrangleitem.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    penwidth.cpp \
    util.cpp

HEADERS += \
    cboardoper.h \
    cboardview.h \
    ccircleitem.h \
    ceraseitem.h \
    citembase.h \
    clineitem.h \
    colorsel.h \
    cpathlineitem.h \
    crectitem.h \
    ctrangleitem.h \
    log.h \
    mainwindow.h \
    penwidth.h \
    util.h

FORMS += \
    colorsel.ui \
    mainwindow.ui \
    penwidth.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    whiteBoardClient.qrc
