Camera::Camera() 
{  // engine = std::shared_ptr<Engine>(new Engine());
    attached_transform = std::shared_ptr<Transform>(new Transform());
    projectionMatrix=glm::perspective(fov, width/height, nearPlane, farPlane);
}

Camera::~Camera()
{

}


glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(attached_transform->getPosition(), attached_transform->getPosition() + attached_transform->forward() ,attached_transform->up());
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

void Camera::move(float &speed, float &deltaTime)
{
    //Keyboard Input
    glm::vec3 position = attached_transform->getPosition();

    //SDL_Log("Left");
    if(Input::keys[SDLK_a])
    {
        position += -(attached_transform->right() * deltaTime * speed);
    }
    //SDL_Log("Right");
    if(Input::keys[SDLK_d])
    {
        position += (attached_transform->right() * deltaTime * speed);
    }
    //SDL_Log("Up");
    if(Input::keys[SDLK_w])
    {
        position += -(attached_transform->forward() * deltaTime * speed);
    }
    //SDL_Log("Down");
    if(Input::keys[SDLK_s])
    {
        position += (attached_transform->forward() * deltaTime * speed);
    }

    std::cout << glm::to_string(position) << std::endl;
    
    attached_transform->setPosition(position);
}

void Camera::look(float &deltaTime, float sensitivity)
{
    Input::mouseDelta = Input::mousePosition - glm::vec2(Input::xPos, Input::yPos); 

    rotation.x -= Input::mouseDelta.y * deltaTime * sensitivity;
    rotation.y += Input::mouseDelta.x * deltaTime * sensitivity; 

    // std::cout<<"Rotation : "<<rotation.x<< ","<<rotation.y<<std::endl;

    glm::vec3 newRotation = glm::vec3(rotation.x, rotation.y, 0.0f);
    attached_transform->rotate(newRotation);

    Input::mousePosition = glm::vec2(Input::xPos, Input::yPos);
}