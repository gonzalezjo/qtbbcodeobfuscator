#pragma once
#include <qstring.h>
#include <functional>

using function = std::function<QString(QString, bool)>;

class Mutation
{
public:
    Mutation(function p_function) : m_function(p_function), m_isOpen(false)
    {
    }
    QString operator()(QString p_message);
    bool isOpen();
private:
    function m_function;
    bool m_isOpen;
};

