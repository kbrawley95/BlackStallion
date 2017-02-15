#include "../include/engine.h"

const int WIDTH=1027;
const int HEIGHT=720;
Graphics* graphics;

Vertex verts[]={

    //Top
    {0.0f, 1.0f, 0.0f,
    1.0f, 0.0f,0.0f, 1.0f}, 

    //Bottom Left
    {-1.0f, -1.0f, 0.0f, 
    0.0f, 1.0f,0.0f, 1.0f},

    //Bottom Right
    {1.0f, -1.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, 1.0f},

    
};

GLuint vertexBufferID;
GLuint elementsBufferID;

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
     bool isRunning=true;
    //Error Checking
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    else{
        SDL_Log("SDL initialized");
    }

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
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_a:
                            SDL_Log("Test");
                            break;

                        case SDLK_ESCAPE:
                            isRunning=false;
                            break;
                    }

                    break;
                }

                case SDL_QUIT:
                    isRunning=false;
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    isRunning=false;
                    break;
                
            }
            update();
            render();
            //Call swap so that GL back buffer is displayed         
            SDL_GL_SwapWindow(window); 
        }

    }
    cleanUp();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::initScene()
{
    //Create Vertex vertexBuffer
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}


void Engine::render()
{
    //Clear the background to black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //Make the new VB0 active. Repeat here as a sanity check(may have changed since Initialisation)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    
    //Establish its 3 coordinates per vertex with zero stride (space between elements)
    //in array and contain floating point numbers (Size of each vertex)
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);

    //The last parameter basically says that the colours start 3 floats into each element of the array
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));

    //Establish array contains vertices(vertices)
    glEnableClientState(GL_VERTEX_ARRAY);
    //Establish array contains colours
    glEnableClientState(GL_COLOR_ARRAY);

    //SwitchtoModelView
    glMatrixMode(GL_MODELVIEW);
    //Reset using the Identity Matrix
    glLoadIdentity();
    //Translateto-5.0fonz-axis
    glTranslatef(0.0f,0.0f,-6.0f);
    //Begindrawingtriangles
    glDrawArrays(GL_TRIANGLES, 0, sizeof(verts)/sizeof(float));

}

void Engine::update()
{
}

void Engine::cleanUp()
{
    glDeleteBuffers(1, &vertexBufferID);
}