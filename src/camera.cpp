Camera::Camera()   
{  // engine = std::shared_ptr<Engine>(new Engine());
    attached_transform = std::shared_ptr<Transform>(new Transform());
    viewMatrix=glm::lookAt(attached_transform->getPosition(), attached_transform->getPosition() + attached_transform->forward() ,attached_transform->up());
    projectionMatrix=glm::perspective(45.0f, 640.0f/480.0f, 0.1f, 100.0f);
}

Camera::~Camera()
{

}

glm::mat4 Camera::getMVPMatrix()
{
    return  projectionMatrix * viewMatrix * attached_transform->getModeltoWorldMatrix();    
}

glm::mat4 Camera::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMatrix;
}