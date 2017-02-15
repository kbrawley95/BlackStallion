#ifndef _ENGINE_H 
#define _ENGINE_H

#include "common.h"

class Engine
{
    public:
    Graphics* graphics;
    SDL_Window* window;
    
    int start();

    private:

    bool eventHandling();
    void update();
    void render();
    SDL_Window* createWindow(const char* windowName);
    

};

#endif 
