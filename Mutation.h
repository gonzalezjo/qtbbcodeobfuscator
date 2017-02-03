#pragma once
#include <qstring.h>
#include <functional>

using function = std::function<QString(QString, bool)>;

class Mutation
{
public:
    Mutation(function f) : m_function(f), m_isOpened(false)
	{		
	}

    QString operator()(QString p_message);
    bool open();
private:
    function m_function;
	bool m_isOpened; 
};

