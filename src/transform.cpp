#include "../include/transform.h"

Engine* engine;

Transform::Transform()
{
    worldMatrix=translate(mat4(1.0f), vec3(0.0f,0.0f,0.0f));
    viewMatrix=lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix=perspective(45.0f, engine->getScreenWidth()/engine->getScreenHeight(), 0.1f, 100.0f);

    
    position = vec3(0.0f,0.0f,0.0f);
    scale = vec3(1.0f,1.0f,1.0f);
    
}

Transform::~Transform()
{
    
}

glm::mat4 Transform::getMVPMatrix()
{
    return  projectionMatrix * viewMatrix * worldMatrix;    
}

glm::mat4 Transform::getWorldMatrix()
{
    return worldMatrix;
}

glm::mat4 Transform::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Transform::getProjectionMatrix()
{
    return projectionMatrix;
}

glm::vec3 Transform::moveForward(float speed)
{
   return vec3(0.0f,0.0f,0.0f);
}

glm::vec3 Transform::moveRight(float speed)
{
    return vec3(0.0f,0.0f,0.0f);
}


glm::vec3 Transform::getPosition()
{
   return position;
}

glm::vec3 Transform::getScale()
{
   return scale;
}

glm::vec3 Transform::getRotation()
{
   return rotation;
}
