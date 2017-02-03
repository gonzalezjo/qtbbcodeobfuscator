#include "Mutation.h"

QString Mutation::operator()(QString p_message)
{
    m_isOpen = !m_isOpen;
    return m_function(p_message, m_isOpen);
}

bool Mutation::isOpen()
{
    return m_isOpen;
}

