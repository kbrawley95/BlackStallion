#ifndef _GAMEOBJECT
#define _GAMEOBJECT

class GameObject
{
    public:
<<<<<<< HEAD
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
=======
        GameObject(std::string givenName)
        {
            name = givenName;
            attached_transform = new Transform();
        }

        std::string getName()
        {
            return name;
        }
        void setName(std::string value)
        {
            name = value;
        }

        Transform* getTransform()
        {
            return attached_transform;
        }

        virtual void render(Camera* mainCamera)
        {
            
        }
        virtual void cleanUp()
        {

        }    
    private:
        std::string name;
        Transform* attached_transform;
>>>>>>> parent of 6c7ae85... Bullet Physics
};

#include "../src/gameobject.cpp"

#endif