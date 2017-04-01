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
    // //Skybox Instance
    skybox = new Skybox("Mountains");
    skybox->getTransform()->setScale(glm::vec3(200,200,200));
    glm::vec3 newScale = skybox->getTransform()->getScale();
    
    // std::cout<<"Name of Object: " << skybox->getName()<<std::endl;
    // printf("Object Scale: x: %f, y: %f, z: %f", newScale.x, newScale.y, newScale.z);
    // // std::cout<<""<<std::endl;

    ui = new UI("HUD", "assets/fonts/OratorStd.otf", 14, "Health: 100%");

    //Instance of Main Camera
    mainCamera=new Camera();
    
    //Collision Management
    collisionManager = new CollisionManager();
    collisionManager->world->addRigidBody(planeCollider->rigidbody);

    model = new OBJModel("Model", "assets/models/teapot.obj", "assets/textures/texture.png");
}

void Engine::eventHandling(SDL_Event event)
{
    Input::update(event);
}

void Engine::update()
{
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime)/1000.0f;
    lastTime = currentTime;

    float newSpeed = 3.0f; 
    float sensitivity = 15.0f; 

    mainCamera->move(newSpeed, deltaTime);
    mainCamera->look(deltaTime, sensitivity);

    glm::quat rotation = mainCamera->attached_transform->getRotation();
    // std::cout<<"Rotation: " <<rotation.x << ", "<<rotation.y<<", "<<rotation.z<<std::endl;
    

    if(Input::keys[SDLK_ESCAPE])
    {
        isRunning = false;
    }

    //MOUSE INPUT

    collisionManager->world->stepSimulation(deltaTime);
    
    
}


void Engine::render()
{ 
    //Clear the background to black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
    //Render Skybox 
    skybox->render(mainCamera);

    model->render(mainCamera);

    
    ui->render(mainCamera);
    //Draw rest of scene 

}

void Engine::cleanUp(SDL_Window* window, SDL_GLContext &glContext) 
{

    skybox->cleanUp();
    model->cleanUp();
    ui->cleanUp();
    collision->cleanUp();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}