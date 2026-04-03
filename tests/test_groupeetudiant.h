#ifndef TEST_GROUPEETUDIANT_H
#define TEST_GROUPEETUDIANT_H

#include <QtTest/QtTest>
#include <groupeetudiant.h>

class TestGroupeEtudiant : public QObject
{
    Q_OBJECT

private slots:
    void testValidationNom();
    void testJSON();
};

#endif // TEST_GROUPEETUDIANT_H
