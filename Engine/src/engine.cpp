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
   
    isMoving=false;
    isRunning=true;

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

    //Generate Application Window
     window=createWindow("Black Stallion");
    //Map OpenGL context to window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // //OpenGL Initialisation
    graphics->initOpenGL();
    initScene();
    graphics->setViewport(Window::WIDTH, Window::HEIGHT);

    //Main Game Loop
    SDL_Event event;
    while(isRunning)
    {
        SDL_Event event;
        //Handle Events (Input)
        eventHandling(event);
        update();
        render();
        //Call swap so that GL back buffer is displayed         
        SDL_GL_SwapWindow(window); 

    }
    cleanUp();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::initScene()
{

    //Skybox Instance
    skybox = new Skybox("Mountains");
    skybox->getTransform()->setScale(200);
    glm::vec3 newScale = skybox->getTransform()->getScale();
    
    std::cout<<"Name of Object: " << skybox->getName()<<std::endl;
    printf("Object Scale: x: %f, y: %f, z: %f", newScale.x, newScale.y, newScale.z);
    // std::cout<<""<<std::endl;

    //Instance of Main Camera
    mainCamera=new Camera();

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

    float newSpeed = 0.2f; 
    float newRot = 0.5f; 

    //Keyboard Input

    if(Input::keys[SDLK_a])
    {
        //SDL_Log("Left");
        glm::vec3 position = -(mainCamera->attached_transform->right() * deltaTime * newSpeed);
        mainCamera->attached_transform->setPosition(position);
    }
    if(Input::keys[SDLK_d])
    {
        //SDL_Log("Right");
        glm::vec3 position = (mainCamera->attached_transform->right() * deltaTime * newSpeed);
        mainCamera->attached_transform->setPosition(position);
    }
    if(Input::keys[SDLK_w])
    {
        //SDL_Log("Up");
        glm::vec3 position = -(mainCamera->attached_transform->forward() * deltaTime * newSpeed);
        mainCamera->attached_transform->setPosition(position);
        
    }
    if(Input::keys[SDLK_s])
    {
        //SDL_Log("Down");
        glm::vec3 position = (mainCamera->attached_transform->forward() * deltaTime * newSpeed);
        mainCamera->attached_transform->setPosition(position);
        
    }
    

    if(Input::keys[SDLK_ESCAPE])
    {
        isRunning = false;
    }

    //MOUSE INPUT
    
}


void Engine::render()
{ 
    //Clear the background to black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
    //Render Skybox 
    skybox->render(mainCamera);
    
    //Draw rest of scene 

}

void Engine::cleanUp()
{
    skybox->cleanUp();
}
