#include "Mutation.h"

QString Mutation::operator()(QString p_message)
{
    m_isOpen = !m_isOpen;
    p_message = m_function(p_message, m_isOpen);
    return p_message;
}

bool Mutation::open()
{
    return m_isOpen;
}

