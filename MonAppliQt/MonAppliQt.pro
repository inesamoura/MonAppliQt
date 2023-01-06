QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mafenetre.cpp

HEADERS += \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/Hardware.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/Librairie.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/MfErrNo.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/Sw_Device.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/Sw_Device.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/Sw_ISO14443A-3.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/Sw_Mf_Classic.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/Tools.h \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/TypeDefs.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/Hardware.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/Librairie.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/MfErrNo.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/ODALID.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/Sw_ISO14443A-3.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/Sw_Mf_Classic.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/Tools.h \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/TypeDefs.h \
    Sw_Device.h \
    mafenetre.h

FORMS += \
    mafenetre.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/ODALID_Education.dll \
    ../../../Downloads/Librairie+sample (1)/Librairie+sample/LIB/libODALID_Education.a \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/ODALID_Education.dll \
    ../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/libODALID_Education.a

unix|win32: LIBS += -L$$PWD/../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB/ -lODALID_Education

INCLUDEPATH += $$PWD/../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB
DEPENDPATH += $$PWD/../../../Downloads/TP-ComSansFil-master/Librairie+sample/LIB

RESOURCES += \
    image.qrc
