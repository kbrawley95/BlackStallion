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
    static const int WIDTH = 1024;
    static const int HEIGHT = 720;

    Engine();
    ~Engine();
    

    private:
    void eventHandling(SDL_Event event);
    void update();
    void render();
    void initScene();
    void cleanUp();
    SDL_Window* createWindow(const char* windowName);


    Graphics* graphics;
    Shader* shader;
    Texture* texture;
    Transform* transform;
    Camera* mainCamera;

    bool isMoving;

    GLuint textureMap;

    GLuint vertexBufferID;
    GLuint elementsBufferID;
    GLuint vertexArrayID;

    float currentTime;
    float lastTime;
    float deltaTime;

    bool isRunning;

    
    int xpos, ypos;
    
    
};

#include "../src/engine.cpp"

#endif 
