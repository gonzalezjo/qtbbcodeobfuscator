#pragma once
#include "Mutation.h"
#include <qlist.h>
#include <iostream>

class StringObfuscator
{
public:
    StringObfuscator();
    static QString obfuscate(QString p_input);
private:
    static QList<Mutation> m_mutations;
};
