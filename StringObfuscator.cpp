#include "StringObfuscator.h"
#include "Helper.h"
#include <iostream>
#include <random>
#include <QDir>
#include <QFile>

using function = std::function<QString(const QString, const bool)>;

extern "C"
{
    #include <luasrc/lua.h>
    #include <luasrc/lauxlib.h>
    #include <luasrc/lualib.h>
}

QList<Mutation> StringObfuscator::p_mutations = { // hashmap would be cool
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
    Mutation([](QString p_message, bool p_opened)
    {
        return p_opened ?
            QString("[color=%1]" + p_message).arg(Helper::color()):
            "[/color]";
    }),
};

StringObfuscator::StringObfuscator()
{
    const QDir l_localQDir = QDir::currentPath() + "/scripts";

    QStringList l_nameFilter;
    l_nameFilter << "*.lua";

    const QFileInfoList scripts = l_localQDir.entryInfoList(l_nameFilter, QDir::Files);

    for (const QFileInfo l_fileInfo : scripts)
    {
        const QString l_pathToFile = l_fileInfo.filePath();
        function l_mutator = [=](QString p_message, bool p_opened) -> QString
        {
            const char* l_luaOutput;
            lua_State* l_state = lua_open();

            luaL_openlibs(l_state);
            luaL_loadfile(l_state, l_pathToFile.toStdString().c_str());
            lua_pcall(l_state, 0, LUA_MULTRET, 0);
            lua_pushstring(l_state, "main");
            lua_gettable(l_state, LUA_GLOBALSINDEX);
            lua_pushstring(l_state, p_message.toStdString().c_str());
            lua_pushboolean(l_state, p_opened);
            lua_pcall(l_state, 2, 1, 0);
            l_luaOutput = lua_tostring(l_state, -1);
            lua_close(l_state);

            return QString(l_luaOutput);
        };
        p_mutations.append(l_mutator);
    }

}


StringObfuscator::~StringObfuscator()
{
}

QString StringObfuscator::obfuscate(QString p_input)
{
    QString l_output = "";

    for (const QChar l_char : p_input)
        l_output += (p_mutations[qrand() % p_mutations.size()])(QString(l_char));

    for (Mutation l_mutation : p_mutations)
        if (l_mutation.open())
            l_output += l_mutation("");

    return l_output;
}
