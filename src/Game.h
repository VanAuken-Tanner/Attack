

//////////////////////////////////////////////
//
//                  Game
//
//////////////////////////////////////////////


#include <string>

#include "..\deps\external\GLEW\include\GL\glew.h"
#include "..\deps\external\GLFW\include\glfw3.h"
#include "..\deps\external\vendor\glm\glm.hpp"
#include "..\deps\external\vendor\glm\gtc\matrix_transform.hpp"
#include "..\deps\external\vendor\imgui\imgui.h"
#include "..\deps\external\vendor\imgui\imgui_impl_glfw.h"
#include "..\deps\external\vendor\imgui\imgui_impl_opengl3.h"

#include "Debug.h"

#include "engine\Renderer.h"
#include "engine\VertexBuffer.h"
#include "engine\IndexBuffer.h"
#include "engine\VertexArray.h"
#include "engine\Texture.h"

//Scenes
#include "scenes\Scene.h"
#include "scenes\Scene_Menu.h"
#include "scenes\Scene_Test.h"
#include "scenes\Scene_Clear.h"
#include "scenes\Scene_Battle.h"

enum GameState{
    Initializing,
    Running,
    Exiting
};

class Game
{
public:
    Game();
    ~Game();

    //memnber
    GameState game_state_;

    void Init();
    void Run();
    void Close();

private:
    GLFWwindow* window_;
};

