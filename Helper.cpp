#include "Helper.h"
#include <qstring.h>

QString Helper::color()
{
    QString l_output = "";

    for (int i = 0; i < 6; i++)
        l_output += QString::number(qrand() % 16, 16);

    return l_output;
}

Helper::Helper()
{
}

Helper::~Helper()
{
}
