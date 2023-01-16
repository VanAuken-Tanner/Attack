#pragma once
#include <string>
#include <iostream>

#include "Globals.h"//TODO - This seems not good.

#include "..\deps\external\GLEW\include\GL\glew.h"

#define ASSERT(x) if(!(x)) Debugger<DEBUG_LEVEL>::Break(__FILE__, __LINE__);

#define LOG_1(x) Debugger<DEBUG_LEVEL>::Log_Console(x);
#define LOG_2(x,y) Debugger<DEBUG_LEVEL>::Log_Console(x,y);
#define LOG_3(x,y,z) Debugger<DEBUG_LEVEL>::Log_Console(x,y,);

//This is a macro used to make OpenGL calls and error check along the way.
#define GL_CALL(x) Debugger<DEBUG_LEVEL>::ClearErrors();\
    x;\
    ASSERT(!Debugger<DEBUG_LEVEL>::CheckErrors(__FILE__, __LINE__ ))

template<int log_level>
class Debugger
{
public:
    template <typename A>
    static void Log_Console(A val)
    {
        if(log_level > 0)
            std::cout << val << "\n";
    }

    template <typename A, typename ... Args>
    static void Log_Console(A first, Args ...args)
    {
        if(log_level > 0)
        {
            std::cout << first;
            Log_Console(args...);
        }
    }

    static void Log_Line()
    {
        if(log_level > 0)
            std::cout << "===========================================" << std::endl;
    }

    static void Break(const char* file, int line)
    {
        if(log_level > 0)
        {
            std::cout << "--------------- BREAK --------------" << std::endl;
            std::cout << "File: " << file << " Line: " << line << std::endl;
            std::cout << "Press any key + enter to continue..." << std::endl;
            std::string input;
            std::cin.clear();
            std::cin >> input;
            std::cin.clear();

            if(input[0] == 'x')
                g_gameState = GameState::Exiting;
        } 
    }

    static void BreakWMessage(std::string sMsg, const char* file, int line)
    {
        if(sMsg != "")
            std::cout << sMsg << std::endl;

        Break(file, line);
    }

    static void ClearErrors()
    {
        while (glGetError() != GL_NO_ERROR);
    };

    static bool CheckErrors(const char* file, int line)
    {
        int errCount = 0; 
        while (GLenum error = glGetError())
        {
            Log_Console("[GL ERROR] ", error);
            Log_Console("File: ", file);
            Log_Console("Line: ", line);
            errCount++;
        }
        return (errCount > 0);
    }
};


