Vertex verts[]={



    /*FRONT*/

    //Top Left
    {glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec4(1.0f, 0.0f,0.0f, 1.0f),
    glm::vec2(0.0f, 1.0f)}, 

    //Bottom Left
    {glm::vec3(-0.5f, -0.5f, 0.5f), 
    glm::vec4(1.0f, 0.0f,0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f)},

    //Bottom Right
    {glm::vec3(0.5f, -0.5f, 0.5f), 
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec2(1.0f, 0.0f)},

    //Top Right
    {glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec4(.0f, 1.0f,0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f)}, 

    /*BACK*/

    //Top Left
    {glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec4(0.0f, 0.0f,1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f)}, 

    //Bottom Left
    {glm::vec3(-0.5f, -0.5f, -0.5f), 
    glm::vec4(0.0f, 0.0f,1.0f, 1.0f),
    glm::vec2(0.0f, 0.0f)},

    //Bottom Right
    {glm::vec3(0.5f, -0.5f, -0.5f), 
    glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f)},

    //Top Right
    {glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec4(0.0f, 1.0f,1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f)}, 

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


std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.

OBJLoader* objLoader;
bool res = objLoader->loadObjModel("cube.obj", vertices, uvs, normals);

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

    mainCamera=new Camera();
    mainCamera->attached_transform->setPosition(glm::vec3(0.0f,0.0f,5.0f));
    shader = new Shader("/textureVS.glsl", "/textureFS.glsl");
    transform = new Transform();

    //Load Texture & Bind it
    std::string texturePath = TEXTURE_PATH + "/metal.jpg";
    textureMap = texture->loadTextureFromFile(texturePath);

    //  std::string textPath = FONT_PATH + "/OratorStd.otf";
    // textureMap = texture->loadTextureFromFont(textPath, 24, "Hello World");


    
    glBindTexture(GL_TEXTURE_2D, textureMap); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);

    


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
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    //Tell the shader that 0 is the position elementsBufferID
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void **)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void **)offsetof(Vertex, colour));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void **)offsetof(Vertex, uvTextCoords));

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


    glBindVertexArray(vertexArrayID);
    glUseProgram(shader->getShaderProgram());

    //Switch on Alpha Blending
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Model-View-Projection Matrix
    GLint MVPLocation = glGetUniformLocation(shader->getShaderProgram(), "MVP");
    GLint texture0Location = glGetUniformLocation(shader->getShaderProgram(), "texture0");

    
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureMap);

    glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(mainCamera->getMVPMatrix()));
	glUniform1i(texture0Location, 0);


    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices.size()));

}

void Engine::cleanUp()
{
    glDeleteTextures(1, &textureMap);
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