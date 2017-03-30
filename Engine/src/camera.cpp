Camera::Camera() 
{  // engine = std::shared_ptr<Engine>(new Engine());
    attached_transform = std::shared_ptr<Transform>(new Transform());
    viewMatrix=glm::lookAt(attached_transform->getPosition(), attached_transform->getPosition() + attached_transform->forward() ,attached_transform->up());
    projectionMatrix=glm::perspective(fov, width/height, nearPlane, farPlane);
}

Camera::~Camera()
{

}


glm::mat4 Camera::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

void Camera::move(float &speed, float &rotate, float &deltaTime)
{
    //Keyboard Input

    if(Input::keys[SDLK_a])
    {
        //SDL_Log("Left");
        glm::vec3 position = -(attached_transform->right() * deltaTime * speed);
        attached_transform->setPosition(position);
    }
    if(Input::keys[SDLK_d])
    {
        //SDL_Log("Right");
        glm::vec3 position = (attached_transform->right() * deltaTime * speed);
        attached_transform->setPosition(position);
    }
    if(Input::keys[SDLK_w])
    {
        //SDL_Log("Up");
        glm::vec3 position = -(attached_transform->forward() * deltaTime * speed);
        attached_transform->setPosition(position);
        
    }
    if(Input::keys[SDLK_s])
    {
        //SDL_Log("Down");
        glm::vec3 position = (attached_transform->forward() * deltaTime * speed);
        attached_transform->setPosition(position);
        
    }
}

void Camera::look()
{
    
}