INCLUDEPATH += $$PWD
QT       += core gui
QT += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controleur_creneau.cpp \
    controleur_ecue.cpp \
    controleur_enseignant.cpp \
    controleur_groupeetudiant.cpp \
    controleur_salle.cpp \
    creneau.cpp \
    creneaudialog.cpp \
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
    supprimercreneaudialog.cpp \
    supprimerecuedialog.cpp \
    supprimerenseignantdialog.cpp \
    supprimergroupeetudiantdialog.cpp \
    supprimersalledialog.cpp \
    tableauxdialog.cpp \
    tests/test_ecue.cpp \
    tests/test_enseignant.cpp \
    tests/test_groupeetudiant.cpp \
    tests/test_salle.cpp

HEADERS += \
    controleur_creneau.h \
    controleur_ecue.h \
    controleur_enseignant.h \
    controleur_groupeetudiant.h \
    controleur_salle.h \
    creneau.h \
    creneaudialog.h \
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
    supprimercreneaudialog.h \
    supprimerecuedialog.h \
    supprimerenseignantdialog.h \
    supprimergroupeetudiantdialog.h \
    supprimersalledialog.h \
    tableauxdialog.h \
    tests/test_ecue.h \
    tests/test_enseignant.h \
    tests/test_groupeetudiant.h \
    tests/test_salle.h

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
