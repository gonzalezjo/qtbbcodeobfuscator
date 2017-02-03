#pragma once
#include "Mutation.h"
#include <qlist.h>
#include <iostream>

class StringObfuscator
{
public:
	StringObfuscator();
	~StringObfuscator();
    static QString obfuscate(QString input);
private:
	static QList<Mutation> p_mutations;
};
