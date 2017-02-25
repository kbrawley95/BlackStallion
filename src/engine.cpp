Vertex verts[]={



    /*FRONT*/

    //Top Left
    {glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec4(1.0f, 0.0f,0.0f, 1.0f)}, 

    //Bottom Left
    {glm::vec3(-0.5f, -0.5f, 0.5f), 
    glm::vec4(1.0f, 0.0f,0.0f, 1.0f)},

    //Bottom Right
    {glm::vec3(0.5f, -0.5f, 0.5f), 
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},

    //Top Right
    {glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec4(.0f, 1.0f,0.0f, 1.0f)}, 

    /*BACK*/

    //Top Left
    {glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec4(0.0f, 0.0f,1.0f, 1.0f)}, 

    //Bottom Left
    {glm::vec3(-0.5f, -0.5f, -0.5f), 
    glm::vec4(0.0f, 0.0f,1.0f, 1.0f)},

    //Bottom Right
    {glm::vec3(0.5f, -0.5f, -0.5f), 
    glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)},

    //Top Right
    {glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec4(0.0f, 1.0f,1.0f, 1.0f)}, 

    };

    GLuint indices[]={
        //front 
        0,1,2,
        0,3,2,

        //left
        4,5,1,
        4,1,0,

        //right
        3,7,2,
        7,6,2,

        //bottom
        1,5,2,
        6,2,5,

        //top
        4,0,7,
        0,7,3,

        //back
        4,5,6,
        4,7,6

    };

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
    WIDTH=1027;
    HEIGHT=720;

    isMoving=false;
    isRunning=true;
    //Error Checking
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    else{
        SDL_Log("SDL initialized");
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
    graphics->setViewport(WIDTH,HEIGHT);

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
    SDL_Quit();
}

void Engine::initScene()
{
    mainCamera=new Camera();
    shader = new Shader("/simpleVS.glsl", "/simpleFS.glsl");
    transform = new Transform();

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //Create Vertex vertexBuffer
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    //Creat Elements (Index)Buffer
    glGenBuffers(1, &elementsBufferID);
    //Make the EBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferID);
    //Copy Index data to the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Tell the shader that 0 is the position elementsBufferID
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void **)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void **)offsetof(Vertex, colour));

}

void Engine::eventHandling(SDL_Event event)
{
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
        SDL_Log("Test");
        mainCamera->attached_transform->setPosition(-(mainCamera->attached_transform->right() * deltaTime * newSpeed));
    }
    if(Input::keys[SDLK_d])
    {
        SDL_Log("Test");
        mainCamera->attached_transform->setPosition(mainCamera->attached_transform->right() * deltaTime * newSpeed);
    }
    if(Input::keys[SDLK_w])
    {
        SDL_Log("Test");
        mainCamera->attached_transform->setPosition(-(mainCamera->attached_transform->forward()* deltaTime * newSpeed));
    }
    if(Input::keys[SDLK_s])
    {
        SDL_Log("Test");
        mainCamera->attached_transform->setPosition(mainCamera->attached_transform->forward() * deltaTime *newSpeed);
    }
    
}

void Engine::render()
{
    //Clear the background to black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    glBindVertexArray(vertexArrayID);
    glUseProgram(shader->getShaderProgram());

    //Model-View-Projection Matrix
    GLint MVPLocation = glGetUniformLocation(shader->getShaderProgram(), "MVP");
    glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(mainCamera->getMVPMatrix()));

    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

}

void Engine::cleanUp()
{
    glDeleteProgram(shader->getShaderProgram());
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