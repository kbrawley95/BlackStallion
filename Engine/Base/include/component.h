#ifndef _COMPONENT_H
#define _COMPONENT_H

class GameObject;
class Camera;
class Component
{
    public:
        GameObject* gameObject = NULL;

        virtual void init(){}
        virtual void update(){}
        virtual void render(Camera* renderer){}
        virtual void cleanUp(){}

};

#endif