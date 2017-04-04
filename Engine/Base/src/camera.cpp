Camera::Camera() 
{  
    attached_transform = std::shared_ptr<Transform>(new Transform());
    projectionMatrix=glm::perspective(fov, width/height, nearPlane, farPlane);
}

Camera::~Camera()
{
   
}

void Camera::update(float &deltaTime, float translationSpeed, float mouseSensitivity)
{
    look(deltaTime, mouseSensitivity);
    move(translationSpeed, deltaTime);
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
    glm::vec3 position = attached_transform->getPosition();

    /*================KEYBOARD INPUT================*/
    //SDL_Log("Left");
    if(Input::keys[SDLK_a])
<<<<<<< HEAD
    {
        position += (getTransform()->right() * deltaTime * speed);
    }

    //SDL_Log("Right");
    if(Input::keys[SDLK_d])
    {
        position -= (getTransform()->right() * deltaTime * speed);
    }

    //SDL_Log("Up");
    if(Input::keys[SDLK_w])
    {
        position += (getTransform()->forward() * deltaTime * speed);
    }

    //SDL_Log("Down");
    if(Input::keys[SDLK_s])
    {
        position -= (getTransform()->forward() * deltaTime * speed);
    }
=======
        position += (attached_transform->right() * deltaTime * speed);

    //SDL_Log("Right");
    if(Input::keys[SDLK_d])
        position -= (attached_transform->right() * deltaTime * speed);

    //SDL_Log("Up");
    if(Input::keys[SDLK_w])
        position += (attached_transform->forward() * deltaTime * speed);

    //SDL_Log("Down");
    if(Input::keys[SDLK_s])
        position -= (attached_transform->forward() * deltaTime * speed);
>>>>>>> origin/master

    getTransform()->setPosition(position);

    /*================CONTROLLER INPUT================*/
    if(Input::buttons[SDL_CONTROLLER_BUTTON_DPAD_LEFT])
        position += (attached_transform->right() * deltaTime * speed);
        
    if(Input::buttons[SDL_CONTROLLER_BUTTON_DPAD_RIGHT])
        position -= (attached_transform->right() * deltaTime * speed);

    if(Input::buttons[SDL_CONTROLLER_BUTTON_DPAD_UP])
        position += (attached_transform->forward() * deltaTime * speed);

    if(Input::buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN])
        position -= (attached_transform->forward() * deltaTime * speed);


    // std::cout << glm::to_string(position) << std::endl;
<<<<<<< HEAD
=======
    attached_transform->setPosition(position);
>>>>>>> origin/master
}

void Camera::look(float &deltaTime, float sensitivity)
{
    Input::mouseDelta = Input::mousePosition - glm::vec2(Input::xPos, Input::yPos); 

    rotation.x -= Input::mouseDelta.y * deltaTime * sensitivity;
    rotation.y += Input::mouseDelta.x * deltaTime * sensitivity; 

    glm::vec3 newRotation = glm::vec3(rotation.x, rotation.y, 0.0f);
    // std::cout<<"Rotation : "<<rotation.x<< ","<<rotation.y<<std::endl;

<<<<<<< HEAD
    getTransform()->rotate(newRotation);
=======
    glm::vec3 newRotation = glm::vec3(rotation.x, rotation.y, 0.0f);
    attached_transform->rotate(newRotation);
>>>>>>> origin/master

    Input::mousePosition = glm::vec2(Input::xPos, Input::yPos);
}