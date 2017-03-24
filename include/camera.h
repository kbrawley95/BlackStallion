#ifndef _CAMERA_H
#define _CAMERA_H

class Camera
{
    public:
    std::shared_ptr<Transform> attached_transform;
    
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

    float fov = 45;
    float width = Window::WIDTH; 
    float height = Window::HEIGHT;
    float nearPlane =0.1f;
    float farPlane = 100.0f;
};

#include "../src/camera.cpp"

#endif