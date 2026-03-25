QT       += core gui
QT += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controleur_ecue.cpp \
    controleur_enseignant.cpp \
    controleur_groupeetudiant.cpp \
    controleur_salle.cpp \
    ecue.cpp \
    ecuedialog.cpp \
    emploidutempsdialog.cpp \
    enseignant.cpp \
    enseignantdialog.cpp \
    groupeetudiant.cpp \
    groupeetudiantdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    salle.cpp \
    salledialog.cpp \
    supprimerecuedialog.cpp \
    supprimerenseignantdialog.cpp \
    supprimergroupeetudiantdialog.cpp \
    supprimersalledialog.cpp \
    test_ecue.cpp \
    test_enseignant.cpp \
    test_groupeetudiant.cpp \
    test_salle.cpp

HEADERS += \
    controleur_ecue.h \
    controleur_enseignant.h \
    controleur_groupeetudiant.h \
    controleur_salle.h \
    ecue.h \
    ecuedialog.h \
    emploidutempsdialog.h \
    enseignant.h \
    enseignantdialog.h \
    groupeetudiant.h \
    groupeetudiantdialog.h \
    mainwindow.h \
    salle.h \
    salledialog.h \
    supprimerecuedialog.h \
    supprimerenseignantdialog.h \
    supprimergroupeetudiantdialog.h \
    supprimersalledialog.h \
    test_ecue.h \
    test_enseignant.h \
    test_groupeetudiant.h \
    test_salle.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    styles/styles.qss \
    styles/styles.qss.txt

RESOURCES += \
    ressource.qrc \
    ressources.qrc
