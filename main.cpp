#include <QtCore/QCoreApplication>
#include "StringObfuscator.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString input = QString("testingmagicalitiness");

    StringObfuscator().obfuscate(input);

    std::cout << input.toStdString() << std::endl;

    return a.exec();
}
