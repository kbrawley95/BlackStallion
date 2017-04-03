#ifndef _ENGINE_H 
#define _ENGINE_H

#include "../../../Engine/Common.h"

class Engine
{
    public:
        SDL_Window* window;
        int start();

    private:
        //External Class Instances
        Skybox* skybox;
        Graphics* graphics;
        Shader* cubeShader;
        Cubemap* cubemap;

        Camera* mainCamera;
        CollisionManager* collisionManager;
        BoxCollider* boxCollider;
        Rigidbody* rigidbody;

        GLuint textureID;
        Texture* texture;

        //Scene Objects
        std::vector<GameObject>sceneObjects; 

        OBJModel* stall;
        BoxCollider* stallBoxCollider;
        Rigidbody* stallRigidbody;


        //Booleans
        bool isRunning;

        //Update Floats
        float currentTime;
        float lastTime;
        float deltaTime;

        //Main Loop Method
        SDL_Window* createWindow(const char* windowName);
        bool initSDL();
        void initScene();
        void eventHandling(SDL_Event event);
        void update();
        void render();
        void cleanUp(SDL_Window* window, SDL_GLContext &glContext); 

};

#include "../src/engine.cpp"

#endif 
