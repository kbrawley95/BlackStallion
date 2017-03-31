#ifndef _CAMERA_H
#define _CAMERA_H

class Camera
{
    public:
    std::shared_ptr<Transform> attached_transform;
    
    Camera();
    ~Camera();

     //OpenGL Vertex Transformations
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    //Camera Movement
    void move (float &speed, float &deltaTime);
    void look (float &deltaTime, float sensitivity);

    private:
        glm::mat4x4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        float fov = 45;
        float width = Window::WIDTH; 
        float height = Window::HEIGHT;
        float nearPlane =0.1f;
        float farPlane = 100.0f;

        glm::vec2 rotation = glm::vec2(0.0f, 0.0f);
};

#include "../src/camera.cpp"

#endif