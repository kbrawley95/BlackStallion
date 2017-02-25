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

    Engine();
    ~Engine();
    

    private:
    void eventHandling(SDL_Event event);
    void update();
    void render();
    void initScene();
    void cleanUp();
    SDL_Window* createWindow(const char* windowName);

     int WIDTH;
     int HEIGHT;

    Graphics* graphics;
    Shader* shader;
    Transform* transform;
    Camera* mainCamera;

    bool isMoving;

    GLuint vertexBufferID;
    GLuint elementsBufferID;
    GLuint vertexArrayID;

    float currentTime;
    float lastTime;
    float deltaTime;

    bool isRunning;
    
    
};
    

#include "../src/engine.cpp"

#endif 
