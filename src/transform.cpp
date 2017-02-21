#include "../include/transform.h"

Engine* engine;

Transform::Transform()
{
    worldMatrix=translate(mat4(1.0f), vec3(0.0f,0.0f,0.0f));
    viewMatrix=lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix=perspective(45.0f, engine->getScreenWidth()/engine->getScreenHeight(), 0.1f, 100.0f);
}

Transform::~Transform()
{
    
}

mat4 Transform::getMVPMatrix()
{
    return  projectionMatrix * viewMatrix * worldMatrix;    
}
