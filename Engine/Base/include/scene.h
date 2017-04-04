#ifndef _SCENE_H
#define _SCENE_H

class Scene
{
    public:
        Scene();
        ~Scene();

        static void init();
        static void render(Camera* mainCamera);
        static void update();
        static void cleanUp();
        static void addCameraToScene(Camera* camera);
        static void addLightToScene(Light* light);
        static void addGameObjectToScene(GameObject* gameObject);

    private:
        static std::vector<Camera*> cameras;
        static std::vector<Light*> lights;
        static std::vector<GameObject*> sceneObjects;
};

std::vector<Camera*> Scene::cameras;
std::vector<Light*> Scene::lights;
std::vector<GameObject*> Scene::sceneObjects;

#include "../src/scene.cpp"

#endif