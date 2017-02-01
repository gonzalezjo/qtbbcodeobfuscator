#include "StringObfuscator.h"
#include "Helper.h"
#include <iostream>
#include <random>
#include <QDir>
#include <QFile>

using Function = std::function<QString(const QString, const bool)>;


extern "C"
{
    #include <luasrc/lua.h>
    #include <luasrc/lauxlib.h>
    #include <luasrc/lualib.h>
}

QList<Mutation> StringObfuscator::mutations = { // hashmap would be cool
    Mutation([](QString message, bool opened)
    {
        return opened ? message.toUpper() : message;
    }),
    Mutation([](QString message, bool opened)
    {
        return opened ? "[i]" + message : message + "[/i]";
    }),
    Mutation([](QString message, bool opened)
    {
        return opened ? "[i]" + message : message + "[/i]";
    }),
    Mutation([](QString message, bool opened)
    {
        return opened ? "[u]" + message : message + "[/u]";
    }),
    Mutation([](QString message, bool opened)
    {
        return opened ? "[s]" + message : message + "[/s]";
    }),
    Mutation([](QString message, bool opened)
    {
        return opened ?
            QString("[color=%1]").arg(Helper::color()):
            "[/color]";
    }),
};

StringObfuscator::StringObfuscator()
{
    QDir localQDir = QDir::currentPath() + "/scripts";

    QStringList nameFilter;
    nameFilter << "*.lua";

    QFileInfoList scripts = localQDir.entryInfoList(nameFilter, QDir::Files);

    for (QFileInfo file : scripts )
    {
        std::function<QString(QString message, bool opened)> f = [&](QString message, bool opened) -> QString
        {
            QString output = file.absolutePath(); // absoluteFilePath = crash. NICE
            std::cout << "PATH: " + file.absoluteFilePath().toStdString() << std::endl;
//            output.truncate(1);
            int error = 0;
            lua_State* state = lua_open();
            luaL_openlibs(state);
            const char* luaOutput;
            if ((error = luaL_loadfile(state, file.absoluteFilePath().toStdString().c_str())) == 0) // the fuck
            {
                if ((error = lua_pcall(state, 0, LUA_MULTRET, 0)) == 0)
                {
                    lua_pushstring(state, "main");
                    lua_gettable(state, LUA_GLOBALSINDEX);
                    lua_pushstring(state, message.toStdString().c_str());
                    lua_pushboolean(state, opened);
                    lua_pcall(state, 2, 1, 0);
                    luaOutput = lua_tostring(state, -1); // or tolstring?
                }
            }
            lua_close(state);
            std::cout << luaOutput << std::endl;
            return QString(luaOutput);
        };
        mutations.append(f);
    }

//    std::for_each(scripts.begin(), scripts.end(), [] (QFileInfo &file)
//    {
//        mutations.append(Mutation([&file](QString message, bool opened)
//        {
//            QString scriptPath = file.absoluteFilePath();
//            int error = 0;
//            std::cout << "path: + scriptPath " + scriptPath.toStdString() << std::endl;
//            lua_State* lua = lua_open();
//            luaL_openlibs(lua);
//            if ((error = luaL_loadfile(lua, scriptPath.toStdString().c_str())) == 0) // the fuck
//            {
//                if ((error = lua_pcall(lua, 0, LUA_MULTRET, 0)) == 0)
//                {
//                    lua_pushstring(lua, "main");
//                    lua_gettable(lua, LUA_GLOBALSINDEX);
//                    lua_pcall(lua, 2, 1, 0);
//                }
//            }
//            lua_close(lua);
//            return 0;
//        }));
//    });
}


StringObfuscator::~StringObfuscator()
{
}

void StringObfuscator::obfuscate(QString& input)
{
	QString output = "";

    for (QChar Char : input)
        output += (mutations[qrand() % mutations.size()])(QString(Char));

    for (Mutation mutation : mutations)
        if (mutation.open())
            output += mutation("");

	input = output;
}
