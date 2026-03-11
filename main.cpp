#include "mainwindow.h"
#include "ecue.h"

#include <iostream>
#include <QString>
#include <QCoreApplication>
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app( argc, argv ) ;
    QString data_path = QCoreApplication::applicationDirPath() + "";
    data_path = QDir(data_path).canonicalPath(); // Simplifie le chemin
    data_path += "/" ;
    std::cout << data_path.toStdString() << std::endl ;


    return 0 ;
}
