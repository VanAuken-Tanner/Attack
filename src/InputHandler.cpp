#include "InputHandler.h"

#include "Globals.h"

void InputHandler::SetKeyState(char symbol, bool state) 
{ 
    KeyActions[symbol].key_.pressed_ = state; 
    KeyActions[symbol].key_.handled_ = false;
}

// template<char sym>
// void InputHandler::AddKeyAction(Action action)


void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            g_gameState = GameState::Exiting;

        if (key == GLFW_KEY_W && action == GLFW_PRESS)
            SetKeyState('w', true); 
        if (key == GLFW_KEY_A && action == GLFW_PRESS)
            SetKeyState('a', true);
        if (key == GLFW_KEY_S && action == GLFW_PRESS)
            SetKeyState('s', true);
        if (key == GLFW_KEY_D && action == GLFW_PRESS)
            SetKeyState('d', true);

        if (key == GLFW_KEY_W && action == GLFW_RELEASE)
            SetKeyState('w', false);
        if (key == GLFW_KEY_A && action == GLFW_RELEASE)
            SetKeyState('a', false);
        if (key == GLFW_KEY_S && action == GLFW_RELEASE)
            SetKeyState('s', false);
        if (key == GLFW_KEY_D && action == GLFW_RELEASE)
            SetKeyState('d', false);

        if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            SetKeyState(' ', false);
}

void InputHandler::ExecuteActions() 
{
    for(int i = 0; i < (int)ActionQueue.size(); i++)
        ActionQueue.at(i).action_(InputHandler::GetKeyState(ActionQueue.at(i).key_.symbol_));
    ActionQueue.clear();
}