#include "../include/transform.h"

Engine* engine;

Transform::Transform()
{
    viewMatrix=glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix=glm::perspective(45.0f, engine->getScreenWidth()/engine->getScreenHeight(), 0.1f, 100.0f);
    
    position = glm::vec3(0.0f,0.0f,0.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    
}

Transform::~Transform()
{
    
}

glm::mat4 Transform::getMVPMatrix()
{
    return  projectionMatrix * viewMatrix * modelMatrix;    
}

glm::mat4x4 Transform::getModeltoWorldMatrix()
{
    //Translation
    modelMatrix = glm::translate(modelMatrix, position);
    
    //Scale
    modelMatrix = glm::scale(modelMatrix, scale);

    //Euler Rotations
    modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    return modelMatrix;
}

glm::mat4 Transform::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Transform::getProjectionMatrix()
{
    return projectionMatrix;
}

glm::vec3 Transform::moveForward()
{
    return glm::vec3(getModeltoWorldMatrix()[2][0],getModeltoWorldMatrix()[2][1],getModeltoWorldMatrix()[2][2]);
}

glm::vec3 Transform::moveUp()
{
    return glm::vec3(getModeltoWorldMatrix()[1][0],getModeltoWorldMatrix()[1][1],getModeltoWorldMatrix()[1][2]);
}

glm::vec3 Transform::moveRight()
{
    return glm::vec3(getModeltoWorldMatrix()[0][0],getModeltoWorldMatrix()[0][1],getModeltoWorldMatrix()[0][2]);
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
