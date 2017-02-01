#include "Helper.h"
#include <qstring.h>

QString Helper::color()
{
    QString output = "";

    for (int i = 0; i < 6; i++)
        output += QString::number(qrand() % 16, 16);

    return output;
}

Helper::Helper()
{
}

Helper::~Helper()
{
}
