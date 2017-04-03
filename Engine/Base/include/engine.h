#ifndef _ENGINE_H 
#define _ENGINE_H

#include "Common.h"

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
        Camera* mainCamera;
        Cubemap* cubemap;

        GLuint textureID;
        Texture* texture;

        //Scene Objects
        std::vector<GameObject>sceneObjects; 

        OBJModel* terrain;

        CollisionManager* collisionManager;
        BoxCollider* boxCollider;
        Rigidbody* rigidbody;

        BoxCollider* terrainBoxCollider;
        Rigidbody* terrainRigidbody;

        UI* ui;

        //Booleans
        bool isMoving;
        bool isRunning;

        glm::vec2 skyboxRotation = glm::vec2(0.0f, 0.0f);

        //Update Floats
        float currentTime;
        float lastTime;
        float deltaTime;

        float yaw;
        float pitch;

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
