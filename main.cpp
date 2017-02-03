#include <QtCore/QCoreApplication>
#include "StringObfuscator.h"
#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication l_application(argc, argv);
    QTextStream l_stream(stdin);
    QString l_output;

    std::cout << "Enter a string to obfuscate.\n" << std::endl;

    l_output = StringObfuscator().obfuscate(l_stream.readLine());

    std::cout << l_output.toStdString() << std::endl;

    return l_application.exec();
}
