#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Common.h"

class Transform
{
    public:

    //OpenGL Vertex Transformations
    glm::mat4 getMVPMatrix();
    glm::mat4 getWorldMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    //Translation Vectors
    glm::vec3 moveForward(float speed);
    glm::vec3 moveRight(float speed);

    //Basic Vector Transformations
    glm::vec3 getPosition();
    glm::vec3 getScale();
    glm::vec3 getRotation();


    Transform();
    ~Transform();
    

    private:
    glm::mat4 worldMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

};

#endif 