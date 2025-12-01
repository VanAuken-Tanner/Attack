#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    game_state_ = GameState::Initializing;

    /* Initialize the library */
    if (!glfwInit())
        return;

    //Before we create our window we are going to setup some open GL 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
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
    LOG_1("Scenes_Regeristerd.");
    
    //The beggining of time!
    double curFrame, deltaTime, prevFrame;

    if(game_state_ != GameState::Exiting)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Setting GameState = Running...\nBeginning main game loop.");
        game_state_ = GameState::Running;
    }

    //Main Game Loop
    /* Loop until the user closes the window_ */
    while (!glfwWindowShouldClose(window_) && game_state_ == GameState::Running)
    {

        //get and update time
        curFrame = glfwGetTime();
        deltaTime = curFrame - prevFrame;
        prevFrame = curFrame;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(pCurrentScene)
        {
            pCurrentScene->OnUpdate(deltaTime);
            pCurrentScene->OnRender();
            pCurrentScene->OnImGuiRender();
            pCurrentScene->OnHandleInput();

            if(pCurrentScene->ExitingScene())
            {
                delete pCurrentScene;
                pCurrentScene = pSceneMenu;
            }

            if(pCurrentScene->ClosingGame())
                game_state_ = GameState::Exiting;
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        GL_CALL(glfwSwapBuffers(window_));

        /* Poll for and process events */
        GL_CALL(glfwPollEvents());

        //Gets and Sets KeyStates
        GL_CALL(glfwSetKeyCallback(window_, InputHandler::key_callback)); 

        //Handle any keys not called by the scene
        InputHandler::HandleKeyEvents();       
             
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