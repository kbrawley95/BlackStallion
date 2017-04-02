#ifndef _GAMEOBJECT
#define _GAMEOBJECT

class GameObject
{
    public:
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
};

#endif