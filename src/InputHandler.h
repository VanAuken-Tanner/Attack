#pragma once
#include <functional>

#include "..\deps\external\GLFW\include\glfw3.h"

using Action = std::function<void(bool)>;

struct KeyData
{
    int  code_;//GLFW_KEY
    bool pressed_;
    bool handled_;
};

struct KeyAction
{
    KeyData key_;
    Action action_;
    void FireAction() {
        action_(key_.pressed_);
        key_.handled_ = true;
    }
};

class InputHandler
{
    
    //inline static std::vector<KeyAction> ActionQueue_;
    inline static std::vector<int> ActionQueue_;
    //inline static std::unordered_map<int, KeyAction> KeyActions_;
    inline static std::unordered_map<int, KeyAction> KeyActions_;

public:

    static void SetKeyHandled(int code_) { KeyActions_[code_].key_.handled_ = true; }
    static void RegisterKeyEvent(int key, bool state);
    static void HandleKeyEvents();

    template<int sym>
    static void AddKeyAction(Action action)
    { 
        KeyActions_[sym].action_ = action;
        KeyActions_[sym].key_.handled_ = true;
        KeyActions_[sym].key_.code_ = sym;
        KeyActions_[sym].key_.pressed_ = false;
    }

    static bool GetKeyState(char symbol) { return KeyActions_[symbol].key_.pressed_; }
    static KeyAction GetKeyAction(char symbol) { return KeyActions_[symbol]; }

    

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};