#include "../include/engine.h"

const int WIDTH=1027;
const int HEIGHT=720;
Graphics* graphics;

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
}


void Engine::render()
{
    //Clear the background to black
    glClearColor(1.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Engine::update()
{
}