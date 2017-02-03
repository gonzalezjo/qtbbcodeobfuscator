#include "StringObfuscator.h"
#include <iostream>
#include <random>
#include <QDir>
#include <QTime>

using function = std::function<QString(const QString, const bool)>;

extern "C"
{
    #include <luasrc/lua.h>
    #include <luasrc/lauxlib.h>
    #include <luasrc/lualib.h>
}

QList<Mutation> StringObfuscator::m_mutations = {
    Mutation([](QString p_message, bool p_opened)
    {
        return p_opened ? p_message.toUpper() : p_message;
    }),
    Mutation([](QString p_message, bool p_opened)
    {
        return p_opened ? "[i]" + p_message : p_message + "[/i]";
    }),
    Mutation([](QString p_message, bool p_opened)
    {
        return p_opened ? "[i]" + p_message : p_message + "[/i]";
    }),
    Mutation([](QString p_message, bool p_opened)
    {
        return p_opened ? "[u]" + p_message : p_message + "[/u]";
    }),
    Mutation([](QString p_message, bool p_opened)
    {
        return p_opened ? "[s]" + p_message : p_message + "[/s]";
    }),
};

StringObfuscator::StringObfuscator()
{
    const QDir l_localQDir = QDir::currentPath() + "/scripts";
    const auto l_fileList = l_localQDir.entryInfoList(QDir::Files);
    lua_State* l_state = luaL_newstate();

    qsrand(QTime::currentTime().msec());

    luaL_openlibs(l_state);
    lua_pcall(l_state, 0, LUA_MULTRET, 0);
    lua_getfield(l_state, LUA_GLOBALSINDEX, "math");
    lua_pushliteral(l_state, "randomseed");
    lua_gettable(l_state, -2);
    lua_remove(l_state, -2);
    lua_pushinteger(l_state, qrand());
    lua_call(l_state, 1, 0);

    for (const QFileInfo l_fileInfo : l_fileList)
    {
        const QString l_pathToFile = l_fileInfo.filePath();
        const function l_mutator = [=](QString p_message, bool p_opened) -> QString
        {
            const char* l_luaOutput;

            luaL_dofile(l_state, l_pathToFile.toStdString().c_str());
            lua_pcall(l_state, 0, LUA_MULTRET, 0);
            lua_pushstring(l_state, "main");
            lua_gettable(l_state, LUA_GLOBALSINDEX);
            lua_pushstring(l_state, p_message.toStdString().c_str());
            lua_pushboolean(l_state, p_opened);
            lua_pcall(l_state, 2, 1, 0);
            l_luaOutput = lua_tostring(l_state, -1);

            return QString(l_luaOutput);
        };
        m_mutations.append(l_mutator);
    }

}


StringObfuscator::~StringObfuscator()
{
}

QString StringObfuscator::obfuscate(QString p_input)
{
    QString l_output = "";

    for (const QChar l_char : p_input)
        l_output += (m_mutations[qrand() % m_mutations.size()])(QString(l_char));

    for (Mutation l_mutation : m_mutations)
        if (l_mutation.isOpen())
            l_output += l_mutation("");

    return l_output;
}
