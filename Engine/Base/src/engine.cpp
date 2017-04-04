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
<<<<<<< HEAD

    /*======COLLISION MANAGEMENT======*/
    collisionManager = new CollisionManager();
=======
     
>>>>>>> parent of 6c7ae85... Bullet Physics

    /*======CLASS INSTANTIATION======*/
    //Skybox Instance
<<<<<<< HEAD
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
=======
    skybox = new Skybox("Mountains");
    skybox->getTransform()->setScale(glm::vec3(200,200,200));
    
    //UI Instance
    ui = new UI("HUD", "assets/fonts/OratorStd.otf", 14, "Health: 100%");

    //Instance of Main Camera
    mainCamera=new Camera();
    mainCamera->attached_transform->setPosition(glm::vec3(-0,10,-145));
>>>>>>> parent of 6c7ae85... Bullet Physics
    
    /*======MODEL LOADING=====*/
    //Model Instance
<<<<<<< HEAD
    GameObject* stallObj = new GameObject("Stall");

    OBJModel* stall = new OBJModel("Model", "assets/models/cube.obj", "assets/textures/plain.png");
    BoxCollider* stallBoxCollider = new BoxCollider(stallObj->getTransform()->getPosition());
    stallObj->getTransform()->setPosition(glm::vec3(0,0,-200));

    Rigidbody* stallRigidbody = new Rigidbody(stallBoxCollider, stallObj->getTransform()->getPosition(),
    stallObj->getTransform()->getRotation(), stallObj->getTransform()->getScale());

    stallObj->addComponent(stall);
    stallObj->addComponent(stallRigidbody);
=======
    terrain = new OBJModel("Model", "assets/models/stall.obj", "assets/textures/trans.png");
    terrain->getTransform()->setPosition(glm::vec3(0,0,-200));
    
    /*======COLLISION MANAGEMENT======*/
    collisionManager = new CollisionManager();

    //Camera Collider
    boxCollider = new BoxCollider(mainCamera->attached_transform->getPosition());
    rigidbody = new Rigidbody(boxCollider, 0.0f, mainCamera->attached_transform->getPosition(),
    mainCamera->attached_transform->getRotation(), mainCamera->attached_transform->getScale()); 
    
    

    //Camera Collider
    terrainBoxCollider = new BoxCollider(terrain->getTransform()->getPosition());
    terrainRigidbody = new Rigidbody(terrainBoxCollider, 0.0f, terrain->getTransform()->getPosition(),
    terrain->getTransform()->getRotation(), terrain->getTransform()->getScale());
>>>>>>> parent of 6c7ae85... Bullet Physics

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

    skyboxRotation.y = deltaTime * newSpeed;
    glm::vec3 newRotation = glm::vec3(0.0f, skyboxRotation.y, 0.0f);

    skybox->getTransform()->rotate(newRotation);

    //COLLISION MANAGEMENT
    collisionManager->update(deltaTime);
    
<<<<<<< HEAD
    // stallRigidbody->update(stall);
    
=======
>>>>>>> parent of 6c7ae85... Bullet Physics
    //INPUT MANAGEMENT
    if(Input::keys[SDLK_ESCAPE])
    {
        isRunning = false;
    }

    // if(Input::buttons[SDL_CONTROLLER_BUTTON_BACK])
    // {
    //     isRunning = false;
    // }

}

void Engine::render()
{ 
    //Clear the background to black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

<<<<<<< HEAD
    Scene::render(mainCamera);
=======
    //Draw rest of scene 
    terrain->render(mainCamera);
    ui->render(mainCamera);
>>>>>>> parent of 6c7ae85... Bullet Physics

}

void Engine::cleanUp(SDL_Window* window, SDL_GLContext &glContext) 
{
<<<<<<< HEAD
    IMG_Quit();
    SDL_Quit();
    
    Scene::cleanUp();
   
=======
    // collisionManager->cleanUp();
    ui->cleanUp();
    terrain->cleanUp();
    skybox->cleanUp();

>>>>>>> parent of 6c7ae85... Bullet Physics
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
