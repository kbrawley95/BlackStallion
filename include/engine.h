#ifndef _ENGINE_H 
#define _ENGINE_H

#include "Common.h"

class Engine
{
    public:
        Engine();
        ~Engine();

        SDL_Window* window;
        int start();

    private:
        //External Class Instances
        Skybox* skybox;
        Graphics* graphics;
        Shader* cubeShader;
        Camera* mainCamera;
        Cubemap* cubemap;

        ObjModel* stall;

        //Scene Objects
        std::vector<GameObject>sceneObjects; 

        //Booleans
        bool isMoving;
        bool isRunning;

        //Update Floats
        float currentTime;
        float lastTime;
        float deltaTime;
        
        //Mouse Coordinates
        int xpos, ypos;

        //Main Loop Method
        void eventHandling(SDL_Event event);
        void update();
        void render();
        void initScene();
        void cleanUp();
        SDL_Window* createWindow(const char* windowName);

    
    
};

#include "../src/engine.cpp"

#endif 
