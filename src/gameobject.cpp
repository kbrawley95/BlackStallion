#include "../include/gameobject.h"

Gameobject::Gameobject(std::string assignedName)
{
    name = assignedName;
}

Gameobject::~Gameobject()
{
    
}

std::string Gameobject::getName()
{
    return name;
}
Transform Gameobject::getTransform()
{
    return transform;
}
