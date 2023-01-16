#pragma once
#include <functional>

#include "..\deps\external\GLFW\include\glfw3.h"

using Action = std::function<void(bool)>;

enum State
{
    pressed,
    Released
};

struct KeyData
{
    char symbol_;
    bool pressed_;
    bool handled_;
};

struct KeyAction
{
    KeyData key_;
    Action action_;
};

class InputHandler
{
    
    inline static std::vector<KeyAction> ActionQueue;
    inline static std::unordered_map<char, KeyAction> KeyActions;
    //inline static std::unordered_map<char,Action> KeyActions_old;
    //inline static std::unordered_map<char,KeyData> KeyState;

public:

    static void SetKeyHandled(char symbol) { KeyActions[symbol].key_.handled_ = true; }
    static void SetKeyState(char symbol, bool state);

    template<char sym>
    static void AddKeyAction(Action action)
    { 
        KeyActions[sym].action_ = action;
        KeyActions[sym].key_.handled_ = true;
        KeyActions[sym].key_.symbol_ = sym;
        KeyActions[sym].key_.pressed_ = false;
    }

    //static bool GetKeyState(char symbol) { return KeyState[symbol]; }
    static bool GetKeyState(char symbol) { return KeyActions[symbol].key_.pressed_; }
    static bool GetIsKeyHandled(char symbol) { return KeyActions[symbol].key_.handled_; }
    static KeyAction GetKeyAction(char symbol) { return KeyActions[symbol]; }

    static unsigned int GetActionCount() { return ActionQueue.size(); }
    
    static void QueueAction(KeyAction keyAction) { ActionQueue.push_back(keyAction);}
    static void ExecuteActions();

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};




// Input_.AddAction('w', []() { 
//         std::cout << "w key: Pressed = "  << std::endl; 
//     });
//     Input_.AddAction('a', []() { 
//         std::cout << "a key: Pressed = " << std::endl; 
//     });
//     Input_.AddAction('s', []() { 
//         std::cout << "s key: Pressed = " <<  std::endl; 
//     });
//     Input_.AddAction('d', []() { 
//         std::cout << "d key: Pressed = "  << std::endl; 
//     });