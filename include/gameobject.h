#ifndef _GAMEOBJECT
#define _GAMEOBJECT

class Gameobject
{
    public:

    Gameobject(std::string assignedName);
    ~Gameobject();
    
    std::string getName();
    Transform getTransform();
    
    private:
    private std::string name;
    Transform* transform;

};

#include "../src/gameobject.cpp"

#endif