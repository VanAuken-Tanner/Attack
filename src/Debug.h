#pragma once
#include <string>
#include <iostream>

#include "GLOBAL_PARAMS.h"//TODO - This seems not good.

#define ASSERT(x) if(!(x)) Debugger::Break(__FILE__, __LINE__);

//This is a macro used to make OpenGL calls and error check along the way.
#define GL_CALL(x) Debugger::ClearErrors();\
    x;\
    ASSERT(!Debugger::CheckErrors(__FILE__, __LINE__ ))

class Debugger
{
public:
    // enum eLogLevel{
    //     None,
    //     All
    // }; 

    // static eLogLevel log_level;

    template <typename A>
    static inline void Log_Console(A val)
    {
        //std::cout << "Log Console Called | Log Level (" << log_level << ")\n";
        //if(log_level > eLogLevel::None)
            std::cout << val << "\n";
    }

    template <typename A, typename ... Args>
    static inline void Log_Console(A first, Args ...args)
    {
        //std::cout << "Log Console Called | Log Level (" << log_level << ")\n";

        //if(log_level > eLogLevel::None)
        {
            std::cout << first;
            Log_Console(args...);
        }
    }

    static void Log_Line();
    static void Break(const char* file, int line);
    static void BreakWMessage(std::string sMsg, const char* file, int line);
    //static void SetLogLevel(eLogLevel level);
    static void ClearErrors();
    static bool CheckErrors(const char* file, int line);
};
