QT       += core gui opengl
LIBS     += -lopengl32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/ColorPallete.cpp \
    src/bintoint.cpp \
    src/levelcreator.cpp \
    src/levelcreatorbrush.cpp \
    src/levelcreatordrawer.cpp \
    src/levelcreatormap.cpp \
    src/leveldrawer.cpp \
    src/levelhandler.cpp \
    src/levellogic.cpp \
    src/levelslist.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/statistic.cpp

HEADERS += \
    src/ColorPallete.h \
    src/FLAGS.h \
    src/bintoint.h \
    src/levelcreator.h \
    src/levelcreatorbrush.h \
    src/levelcreatordrawer.h \
    src/levelcreatormap.h \
    src/leveldrawer.h \
    src/levelhandler.h \
    src/levellogic.h \
    src/levelslist.h \
    src/mainwindow.h \
    src/statistic.h \
    src/statusEnums.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    stat.qrc \
    textures.qrc

DISTFILES +=
