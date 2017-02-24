#ifndef _ENGINE_H 
#define _ENGINE_H

#include "Common.h"

class Engine
{
    public:
    SDL_Window* window;
    int start();
    float getScreenWidth();
    float getScreenHeight();
    

    private:
    void eventHandling(SDL_Event event);
    void update();
    void render();
    void initScene();
    void cleanUp();
    SDL_Window* createWindow(const char* windowName);
    

};

#endif 
