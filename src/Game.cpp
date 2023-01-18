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
    
    //ASSERT(false);

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

    if(g_gameState != GameState::Exiting)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Setting GameState = Running...\nBeggining main game loop.");
        g_gameState = GameState::Running;
    }

    //https://stackoverflow.com/questions/12574565/moving-object-stutters-using-delta-time-to-unify-speed
    //#define TAU (M_PI * 2.0)
    // a += deltaTime * speed;
    // // Optional, keep the cycle bounded to reduce precision errors
    // // if you plan to leave this running for a long time...
    // if( a > TAU ) a -= TAU;
    // x = sin( a ) * 0.8f;
    // y = cos( a ) * 0.8f;


    //The beggining of time!
    double curFrame, deltaTime, prevFrame;

    //Begin InputHandling
    

    InputHandler::AddKeyAction<'w'>([](bool pressed) { 
        std::cout << "w key: Pressed!!" << std::endl; 
    });

    InputHandler::AddKeyAction<'a'>([](bool pressed) {
        std::cout << "a key: Pressed!!" << std::endl;

    });

    InputHandler::AddKeyAction<'s'>([](bool pressed) { 
        std::cout << "s key: Pressed!!" << std::endl; 
    });

    InputHandler::AddKeyAction<'d'>( [](bool pressed) { 
        std::cout << "d key: Pressed!!" << std::endl; 
    });

    InputHandler::AddKeyAction<' '>( [](bool pressed) { 
        std::cout << "space key pressed." << std::endl;
        ASSERT(false); 
    });

    //Main Game Loop
    /* Loop until the user closes the window_ */
    while (!glfwWindowShouldClose(window_) && g_gameState == GameState::Running)
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

        //Gets and Sets KeyStates
        GL_CALL(glfwSetKeyCallback(window_, InputHandler::key_callback)); 


        if(!InputHandler::GetIsKeyHandled('w'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('w'));
            InputHandler::SetKeyHandled('w');
            
        }

        if(!InputHandler::GetIsKeyHandled('a'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('a'));
            InputHandler::SetKeyHandled('a');
            
        }

        if(!InputHandler::GetIsKeyHandled('s'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('s'));
            InputHandler::SetKeyHandled('s');
            
        }

        if(!InputHandler::GetIsKeyHandled('d'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('d'));
            InputHandler::SetKeyHandled('d');
            
        }

        if(!InputHandler::GetIsKeyHandled(' '))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction(' '));
            InputHandler::SetKeyHandled(' ');
            
        }

        if(InputHandler::GetActionCount() > 0)
        {
            InputHandler::ExecuteActions();        
            //ASSERT(false);
        }
             
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