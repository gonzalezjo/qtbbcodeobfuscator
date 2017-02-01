#pragma once
#include <qstring.h>
#include <functional>

using Function = std::function<QString(QString, bool)>;

class Mutation
{
public:
    Mutation(Function f) : f_(f), isOpened_(false), wasUsed_(false) // initializer list
	{		
	}

	QString operator()(QString message);
	bool open();

private:
    Function f_;
	bool isOpened_; 
	bool wasUsed_;
};

