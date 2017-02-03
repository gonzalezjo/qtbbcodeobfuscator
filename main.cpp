#include <QtCore/QCoreApplication>
#include "StringObfuscator.h"
#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication l_application(argc, argv);

    std::cout << "Enter a string to obfuscate." << std::endl;

    QTextStream l_stream(stdin);

    const QString l_output = StringObfuscator().obfuscate(l_stream.readLine());

    std::cout << l_output.toStdString() << std::endl;

    return l_application.exec();
}
