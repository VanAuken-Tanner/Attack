#include "Debug.h"

#include "..\deps\external\GLEW\include\GL\glew.h"
//#include "..\..\deps\external\GLFW\include\glfw3.h"


void Debugger::Log_Line()
{
    //if(log_level > eLogLevel::None)
        std::cout << "===========================================" << std::endl;
}

void Debugger::Break(const char* file, int line)
{
    //if(log_level < eLogLevel::All)
        //return;

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

void Debugger::BreakWMessage(std::string sMsg, const char* file, int line)
{
    if(sMsg != "")
        std::cout << sMsg << std::endl;

    Break(file, line);
}

// void Debugger::SetLogLevel(eLogLevel level)
// {
//     log_level = level;

//     Debugger::Log_Line();
//     Debugger::Log_Console("Debug Level (", log_level, ")");
//     Debugger::Log_Line();
// }

void Debugger::ClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
};

bool Debugger::CheckErrors(const char* file, int line)
{
    int errCount = 0;
    while (GLenum error = glGetError())
    {
        Debugger::Log_Console("[GL ERROR] ", error);
        Debugger::Log_Console("File: ", file);
        Debugger::Log_Console("Line: ", line);
        errCount++;
    }
    return (errCount > 0);
};


