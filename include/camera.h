#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"

class Camera
{
    public:
     //OpenGL Vertex Transformations
    glm::mat4 getMVPMatrix();
    glm::mat4 getModeltoWorldMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    
    Camera();
    ~Camera();


    private:

    glm::mat4x4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

};


#endif