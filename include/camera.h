#ifndef _CAMERA_H
#define _CAMERA_H

class Camera
{
    public:
    std::shared_ptr<Transform> attached_transform;
   // std::shared_ptr<Engine> engine;
    
    Camera();
    ~Camera();

     //OpenGL Vertex Transformations
    glm::mat4 getMVPMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    private:
    glm::mat4x4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;


};

#include "../src/camera.cpp"

#endif