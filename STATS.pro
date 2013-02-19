QT       += core gui

TARGET = STATS
TEMPLATE = app

SOURCES += main.cpp \
    Widget_POPULATION.cpp \
    TEXT_MAJ.cpp \
    TEST_MODEL_SIMPLE.cpp \
    TABLEAU.cpp \
    System\SYSTEM.cpp \
    ResumMulti.cpp \
    System\QBoolList.cpp \
    POP_EDITION_TYPE.cpp \
    POP_EDITION_NOM.cpp \
    MENU_GRAPH.cpp \
    System\Maths.cpp \
    LIS_QWidget.cpp \
    Fenetre\DOCK_TAP.cpp \
    Fenetre\Dock_Indicateurs.cpp \
    DialAssistant.cpp \
    DIAL_VAL_MANQUANTES.cpp \
    DIAL_CONV_ORD.cpp \
    dial_conv_bin.cpp \
    Assistant.cpp \
    dial_regrouper_val.cpp \
    Population/dialog_creationpop.cpp \
    Fenetre/FENETRE_TABLEAU.cpp \
    Fenetre/FENETRE_PRINCIPALE.cpp \
    Fenetre/FENETRE_POPULATION.cpp \
    Graph/Histogram.cpp \
    DOCK_GRAPHDISTRIB.cpp \
    Population/POPULATION.cpp \
    Graph/Bar_Chart.cpp \
    Resume/Resume.cpp \
    Resume/TAP/TAP_Donnes.cpp \
    Resume/TAP/TAP.cpp \
    Population/QStringTable.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    STATS280.png \
    STATS264.png \
    STATS2_harmattan.desktop \
    STATS2.svg \
    STATS2.pro.user \
    STATS2.pro \
    STATS2.desktop \
    CreateBarres.js \
    BarreChart.qml \
    Barre.qml

HEADERS += \
    Widget_POPULATION.h \
    TYPES.h \
    TEXT_MAJ.h \
    TEST_MODEL_SIMPLE.h \
    System\TablePlus.h \
    TABLEAU.h \
    System\SYSTEM.h \
    ResumMulti.h \
    Population\QStringTable.h \
    System\QIntList.h \
    System\QBoolList.h \
    QActionList.h \
    POP_EDITION_TYPE.h \
    POP_EDITION_NOM.h \
    MENU_GRAPH.h \
    System\Maths.h \
    main.h \
    LIS_QWidget.h \
    Fenetre\FENETRE_PRINCIPALE.h \
    FENETRE_MENU.h \
    Fenetre\DOCK_TAP.h \
    Fenetre\Dock_Indicateurs.h \
    DialAssistant.h \
    DIAL_VAL_MANQUANTES.h \
    DIAL_CONV_ORD.h \
    dial_conv_bin.h \
    Assistant.h \
    VAL_GROUP.h \
    dial_regrouper_val.h \
    Population/dialog_creationpop.h \
    Graph/Histogram.h \
    DOCK_GraphDistrib.h \
    Population/POPULATION.h \
    Graph/Bar_Chart.h \
    Fenetre/FENETRE_POPULATION.h \
    Resume/Resume.h \
    Resume/TAP/TAP_Donnes.h \
    Resume/TAP/TAP_Croise.h \
    Resume/TAP/TAP.h

FORMS += \
    dial_conv_bin.ui \
    dial_regrouper_val.ui \
    Population/dialog_creationpop.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/qwt-6.1.0-rc2/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/qwt-6.1.0-rc2/lib/debug/ -lqwt
else:symbian: LIBS += -lqwt
else:unix: LIBS += -L$$PWD/../../../../../usr/local/qwt-6.1.0-rc2/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../usr/local/qwt-6.1.0-rc2/include
DEPENDPATH += $$PWD/../../../../../usr/local/qwt-6.1.0-rc2/include
