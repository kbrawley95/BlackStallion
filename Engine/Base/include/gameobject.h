#ifndef _GAMEOBJECT
#define _GAMEOBJECT

class GameObject
{
    public:
        GameObject(std::string givenName)
        {
            name = givenName;
            transform = new Transform();
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
            return transform;
        }

        virtual void render()
        {
            
        }
        virtual void cleanUp()
        {

        }    
    private:
        std::string name;
        Transform* transform;
};

#endif