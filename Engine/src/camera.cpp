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