#pragma once
#include "Mutation.h"
#include <qlist.h>
#include <iostream>

class StringObfuscator
{
public:
	StringObfuscator();
	~StringObfuscator();
	static void obfuscate(QString& input);
private:
	static QList<Mutation> mutations;
};
