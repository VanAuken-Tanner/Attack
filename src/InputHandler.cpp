#include "InputHandler.h"


void InputHandler::RegisterKeyEvent(int code_, bool state) 
{ 
    KeyActions_[code_].key_.pressed_ = state; 
    KeyActions_[code_].key_.handled_ = false;
    ActionQueue_.push_back(code_);
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_ESCAPE, true); 

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_W, true); 
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_A, true);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_S, true);
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_D, true);
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_Q, true);
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_E, true);
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_E, true);
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_F, true);

    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_W, false);
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_A, false);
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_S, false);
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_D, false);
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_Q, false);
    if (key == GLFW_KEY_E && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_E, false);
    if (key == GLFW_KEY_R && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_R, false);
    if (key == GLFW_KEY_F && action == GLFW_RELEASE)
        RegisterKeyEvent(GLFW_KEY_F, false);

    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        RegisterKeyEvent(GLFW_KEY_SPACE, false);
}

void InputHandler::HandleKeyEvents() 
{
    for(int i = 0; i < (int)ActionQueue_.size(); i++)
    {
        KeyActions_[ActionQueue_.at(i)].FireAction();
    }
    ActionQueue_.clear();
}

