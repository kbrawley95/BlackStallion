#include "../include/camera.h"

   Engine* engine;
   Transform* attached;

Camera::Camera()
{   attached = new Transform();
    viewMatrix=glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix=glm::perspective(45.0f, engine->getScreenWidth()/engine->getScreenHeight(), 0.1f, 100.0f);
}

Camera::~Camera()
{

}

glm::mat4 Camera::getMVPMatrix()
{
    return  projectionMatrix * viewMatrix * modelMatrix;    
}

glm::mat4x4 Camera::getModeltoWorldMatrix()
{
    glm::mat4x4 model_matrix = glm::mat4x4(1.0f);
    
    //Translation
    model_matrix = glm::translate(model_matrix, attached->getPosition());

    //Euler Rotations
    model_matrix = glm::rotate(model_matrix, attached->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, attached->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, attached->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

    //Scale
    model_matrix = glm::scale(model_matrix, attached->getScale());

    return model_matrix;
}

glm::mat4 Camera::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMatrix;
}