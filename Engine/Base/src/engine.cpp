SDL_Window* Engine::createWindow(const char* windowName)
{
    SDL_Window* window = SDL_CreateWindow(windowName, //Window Title 
                        SDL_WINDOWPOS_CENTERED, //x
                        SDL_WINDOWPOS_CENTERED, //y
                        Window::WIDTH,  //Width
                        Window::HEIGHT, //Height
                        SDL_WINDOW_OPENGL); //Flags

    return window;
} 

int Engine::start()
{
    //SDL Initialisation Error Checking
    initSDL();

    //Generate Application Window
    window=createWindow("Black Stallion");

    //Map OpenGL context to window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    //OpenGL Initialisation
    graphics->initOpenGL();
    //Environment Scene Initialisation
    initScene();
    //Configure Viewport
    graphics->setViewport(Window::WIDTH, Window::HEIGHT);

    //Main Game Loop
    SDL_Event event;
    while(isRunning)
    {
        //Handle Events (Input)
        eventHandling(event);
        update();
        render();
        //Call swap so that GL back buffer is displayed         
        SDL_GL_SwapWindow(window); 

    }

    //Free Resources
    cleanUp(window, glContext);
}

bool Engine::initSDL()
{
    /*SDL ERROR CHECKING*/
    if (SDL_Init(SDL_INIT_NOPARACHUTE & SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    else{
        SDL_Log("SDL initialized");
    }
    /*SDL_IMAGE ERROR CHECKING*/
    int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags) & (imageInitFlags)) != imageInitFlags)	{

		std::cout << "ERROR SDL_Image Init “ << IMG_GetError() << endl";
	}

    /*TTF (Fonts) ERROR CHECKING*/
    if (((returnInitFlags) & (imageInitFlags)) != imageInitFlags)	{

		std::cout << "ERROR SDL_Image Init" << IMG_GetError() << std::endl;
	}

	if (TTF_Init() == -1)	{
		std::cout << "ERROR	TTF_Init: " << TTF_GetError();
	}

    //Specify OpenGL Version (4.2)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    isRunning = true;

    return true;
}

void Engine::initScene()
{   

    /*======COLLISION MANAGEMENT======*/
    collisionManager = new CollisionManager();

    /*======SKYBOX======*/
    //Skybox Instance
    Cubemap* cubemap = new Cubemap();
    cubemap->cubemap->addComponent(cubemap);
    Scene::addGameObjectToScene(cubemap->cubemap);
    
    /*======CAMERA======*/
    mainCamera=new Camera("Camera 1");
    mainCamera->getTransform()->setPosition(glm::vec3(-0,0,-100));
    BoxCollider* boxCollider = new BoxCollider(mainCamera->getTransform()->getPosition());
    Rigidbody* rigidbody = new Rigidbody(boxCollider,  mainCamera->getTransform()->getPosition(),
    mainCamera->getTransform()->getRotation(), mainCamera->getTransform()->getScale());
    mainCamera->addComponent(rigidbody);
    Scene::addCameraToScene(mainCamera); 
    
    /*======STALL=====*/
    //Model Instance
    GameObject* stallObj = new GameObject("Stall");

    OBJModel* stall = new OBJModel("Model", "assets/models/cube.obj", "assets/textures/plain.png");
    BoxCollider* stallBoxCollider = new BoxCollider(stallObj->getTransform()->getPosition());
    stallObj->getTransform()->setPosition(glm::vec3(0,0,-200));

    Rigidbody* stallRigidbody = new Rigidbody(stallBoxCollider, stallObj->getTransform()->getPosition(),
    stallObj->getTransform()->getRotation(), stallObj->getTransform()->getScale());

    stallObj->addComponent(stall);
    stallObj->addComponent(stallRigidbody);

    Scene::addGameObjectToScene(stallObj);
}

void Engine::eventHandling(SDL_Event event)
{
    // Input::checkForControllers();
    Input::update(event);
}

void Engine::update()
{
    //Calculate time (in seconds) that has passed
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime)/1000.0f;
    lastTime = currentTime;

    //MOUSE INPUT
    float newSpeed = 8.0f; 
    float sensitivity = 15.0f; 
    mainCamera->update(deltaTime, newSpeed, sensitivity);

    //COLLISION MANAGEMENT
    collisionManager->update(deltaTime);
    
    // stallRigidbody->update(stall);
    
    //INPUT MANAGEMENT
    if(Input::keys[SDLK_ESCAPE])
    {
        isRunning = false;
    }

}

void Engine::render()
{ 
    //Clear the background to black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    Scene::render(mainCamera);

}

void Engine::cleanUp(SDL_Window* window, SDL_GLContext &glContext) 
{
    IMG_Quit();
    SDL_Quit();
    
    Scene::cleanUp();
   
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}
