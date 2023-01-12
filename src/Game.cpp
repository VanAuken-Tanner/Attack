#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    g_gameState = GameState::Initializing;
       
    Debugger<DEBUG_LEVEL>::Log_Console("Debugging set and enabled.");


    /* Initialize the library */
    if (!glfwInit())
        return;

    //Before we create our window_ we are going to setup some open GL 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a window_ed mode window_ and its OpenGL context */
    window_ = glfwCreateWindow(1600, 900, "Attack!", NULL, NULL);
    if (!window_)
    {
        glfwTerminate();
        return;
    }

    /* Make the window_'s context current */
    glfwMakeContextCurrent(window_);

    if(glewInit() != GLEW_OK)
        Debugger<DEBUG_LEVEL>::Log_Console("Failed to init glew");

    //Log(glGetString(GL_VERSION));
    std::cout << glGetString(GL_VERSION) << std::endl;
}

void Game::Run()
{
    //blender function
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //IMGUI - initialization starts here
    const char* glsl_version = "#version 330";
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    Scene* pCurrentScene = nullptr;
    Scene_Menu* pSceneMenu = new Scene_Menu(pCurrentScene);
    pCurrentScene = pSceneMenu; 
    pSceneMenu->RegisterTest<Scene_Test>("Scene Test");
    pSceneMenu->RegisterTest<Scene_Clear>("Clear Color");
    pSceneMenu->RegisterTest<Scene_Battle>("Battle Scene");

    if(g_gameState != GameState::Exiting)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Setting GameState = Running...\nBeggining main game loop.");
        g_gameState = GameState::Running;
    }

    //Main Game Loop
    /* Loop until the user closes the window_ */
    while (!glfwWindowShouldClose(window_) && g_gameState == GameState::Running)
    {
        // GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
        // GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(pCurrentScene)
        {
            pCurrentScene->OnUpdate(0);
            pCurrentScene->OnRender();
            pCurrentScene->OnImGuiRender();
            pCurrentScene->OnHandleInput(window_);

            if(pCurrentScene->Exiting())
            {
                delete pCurrentScene;
                pCurrentScene = pSceneMenu;
            }
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        GL_CALL(glfwSwapBuffers(window_));

        /* Poll for and process events */
        GL_CALL(glfwPollEvents());

        //handle events
             
    }

    if(pCurrentScene != pSceneMenu)
        delete pSceneMenu;
    delete pCurrentScene;


}

void Game::Close()
{
    //ImGui shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    
    glfwTerminate();

    Debugger<0>::Log_Console("Ending Application...");
}