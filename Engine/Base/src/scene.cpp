Scene::Scene()
{
    init();
}

Scene::~Scene()
{
    cleanUp();
}

void Scene::init()
{
    for(int i = 0; i<sceneObjects.size(); i++)
    {
        sceneObjects[i]->getAttachedComponents()[i]->init();
    }
}


void Scene::render(Camera* mainCamera)
{
    for(int i = 0; i<sceneObjects.size(); i++)
    {
        sceneObjects[i]->getAttachedComponents()[i]->render(mainCamera);
    }
}

void Scene::cleanUp()
{
    for(int i = 0; i < sceneObjects.size(); i++)
    {
        sceneObjects[i]->getAttachedComponents()[i]->cleanUp();
        delete sceneObjects[i];
    }
}

void Scene::addGameObjectToScene(GameObject* gameObject)
{
    sceneObjects.push_back(gameObject);
}

void Scene::addCameraToScene(Camera* camera)
{
    cameras.push_back(camera);
}

void Scene::addLightToScene(Light* light)
{
    lights.push_back(light);
}