#ifndef TEST_SALLE_H
#define TEST_SALLE_H

#include <QtTest/QtTest>
#include <salle.h>

class TestSalle : public QObject
{
    Q_OBJECT

private slots:
    void testValidationNumero();
    void testValidationType();
    void testJSON();
};

#endif // TEST_SALLE_H
