#ifndef _CAMERA_H
#define _CAMERA_H

class Camera : public GameObject
{
    public:
    Camera(std::string name);
    ~Camera();

    void update(float &deltaTime, float translationSpeed, float mouseSensitivity);

     //OpenGL Vertex Transformations
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    //Camera Movement
    void move (float &speed, float &deltaTime);
    void look (float &deltaTime, float sensitivity);

    private:
        glm::mat4 projectionMatrix;
        glm::vec2 rotation = glm::vec2(0,0);

        float fov = 45;
        float width = Window::WIDTH; 
        float height = Window::HEIGHT;
        float nearPlane =0.1f;
        float farPlane = 1000.0f;
       
};

#include "../src/camera.cpp"

#endif