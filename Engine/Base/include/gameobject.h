#ifndef _GAMEOBJECT
#define _GAMEOBJECT

class GameObject
{
    public:
        GameObject(std::string givenName);
        ~GameObject();

        std::string getName();
        void setName(std::string value);
      
        Transform* getTransform();
        void addComponent(Component* component);
        std::vector<Component*> getAttachedComponents();
        
    protected:
        std::string name;
        Transform* transform;
        std::vector<Component*> attached_components;
};

#include "../src/gameobject.cpp"

#endif