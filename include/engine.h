#ifndef ENGINE_H 
#define ENGINE_H

#include "common.h"

class Engine
{
    public:
    //Game* game;
    SDL_Window* window;
    
    int start();

    private:

    bool eventHandling();
    void update();
    void render();
    SDL_Window* createWindow(const char* windowName);
    

};

#endif 
