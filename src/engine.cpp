Engine::Engine()
{
    
}

Engine::~Engine()
{

}

SDL_Window* Engine::createWindow(const char* windowName)
{
    SDL_Window* window = SDL_CreateWindow(windowName, //Window Title 
                        SDL_WINDOWPOS_CENTERED, //x
                        SDL_WINDOWPOS_CENTERED, //y
                        WIDTH, //Width
                        HEIGHT, //Height
                        SDL_WINDOW_OPENGL); //Flags

    return window;
} 

int Engine::start()
{
   
    isMoving=false;
    isRunning=true;


    /*SDL ERROR CHECKING*/
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
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
    graphics->setViewport(Engine::WIDTH,Engine::HEIGHT);

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
    //Instance of Main Camera
    mainCamera=new Camera();
    //Main Camera initial start position
    mainCamera->attached_transform->setPosition(glm::vec3(0.0f,0.0f,5.0f));

    //Shaders 
    cubeShader = new Shader("/textureVS.glsl", "/textureFS.glsl");

    //Transform
    transform = new Transform();

    //Load Cube Texture & Bind it
    std::string texturePath = TEXTURE_PATH + "/metal.jpg";
    textureMap = texture->loadTextureFromFile(texturePath);

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //Create Vertex vertexBuffer
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
    glBufferData(GL_ARRAY_BUFFER, Cube::m_vertices.size() * sizeof(Vertex), &Cube::m_vertices[0], GL_STATIC_DRAW);

    //Create Elements (Index)Buffer
    glGenBuffers(1, &elementsBufferID);
    //Make the EBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferID);
    //Copy Index data to the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Cube::m_indices.size() * sizeof(GLuint), &Cube::m_indices[0], GL_STATIC_DRAW);

    //Tell the shader that 0 is the position 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    //Tell the shader that 1 is the colour 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, colour));

    //Tell the shader that 2 is the texture coordinates 
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uvTextCoords));
}

void Engine::eventHandling(SDL_Event event)
{
    float camera_rotation = 0.0f;
     glm::vec3 offset =  glm::vec3(mainCamera->attached_transform->up() * 0.5f);
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                Input::keys[event.key.keysym.sym]=true;
                break;

            case SDL_KEYUP:
                Input::keys[event.key.keysym.sym]=false;
                break;
            
            case SDL_MOUSEMOTION:

                xpos = event.button.x;
                ypos = event.button.y;

                if(event.button.x < (Engine::WIDTH))
                    // mainCamera->attached_transform->lookHorizontal(60.0f);
                if(event.button.y < (Engine::HEIGHT))
                    mainCamera->attached_transform->lookHorizontal(60.0f);    

                std::cout << "Mouse = (" << xpos << ", " << ypos << ")" << std::endl;
                break;
            
            case SDL_QUIT:
                isRunning=false;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                isRunning=false;
                break;
        }
    }
}

void Engine::update()
{
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime)/1000.0f;
    lastTime = currentTime;


    float newSpeed = 1.0f; 

    if(Input::keys[SDLK_a])
    {
        //SDL_Log("Left");
        mainCamera->attached_transform->setPosition(-(mainCamera->attached_transform->right() * deltaTime * newSpeed));
    }
    if(Input::keys[SDLK_d])
    {
        //SDL_Log("Right");
        mainCamera->attached_transform->setPosition(mainCamera->attached_transform->right() * deltaTime * newSpeed);
    }
    if(Input::keys[SDLK_w])
    {
        //SDL_Log("Up");
        mainCamera->attached_transform->setPosition(-(mainCamera->attached_transform->forward()* deltaTime * newSpeed));
        printf("x: %f, y: %f, z: %f\n", mainCamera->attached_transform->getPosition().x, mainCamera->attached_transform->getPosition().y, mainCamera->attached_transform->getPosition().z);
        
    }
    if(Input::keys[SDLK_s])
    {
        //SDL_Log("Down");
        mainCamera->attached_transform->setPosition(mainCamera->attached_transform->forward() * deltaTime *newSpeed);
        printf("x: %f, y: %f, z: %f\n", mainCamera->attached_transform->getPosition().x, mainCamera->attached_transform->getPosition().y, mainCamera->attached_transform->getPosition().z);
        
    }

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

    //Bind Vertex Array Object to pipeline (Sanity Check)
    glBindVertexArray(vertexArrayID);

    //Use the specified shader program
    glUseProgram(cubeShader->getShaderProgram());

    //Switch on Alpha Blending
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Model-View-Projection Matrix
    GLint MVPLocation = glGetUniformLocation(cubeShader->getShaderProgram(), "MVP");
    glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(mainCamera->getMVPMatrix()));

    //Cube Texture
    GLint texture0Location = glGetUniformLocation(cubeShader->getShaderProgram(), "texture0");
	glUniform1i(texture0Location, 0);

    //Draw vertices data based on index selection values
    glDrawElements(GL_TRIANGLES, Cube::m_indices.size(), GL_UNSIGNED_INT, 0);
   

}

void Engine::cleanUp()
{
    glDeleteTextures(1, &textureMap);
    glDeleteProgram(cubeShader->getShaderProgram());
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &elementsBufferID);
    glDeleteBuffers(1, &vertexArrayID);
}

float Engine::getScreenWidth()
{
    return (float)WIDTH;
}

float Engine::getScreenHeight()
{
    return (float)HEIGHT;
}