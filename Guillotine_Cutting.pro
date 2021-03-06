QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_ss.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    project.cpp \
    projectrect.cpp \
    savingchanges.cpp

HEADERS += \
    add_ss.h \
    form.h \
    mainwindow.h \
    project.h \
    projectrect.h \
    savingchanges.h

FORMS += \
    add_ss.ui \
    mainwindow.ui \
    savingchanges.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

