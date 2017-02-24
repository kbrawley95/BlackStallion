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
    return  projectionMatrix * viewMatrix * getModeltoWorldMatrix();    
}

glm::mat4x4 Camera::getModeltoWorldMatrix()
{
    glm::mat4x4 model_matrix = glm::mat4x4(1.0f);
    
    //Translation
    model_matrix = glm::translate(model_matrix, attached_transform->getPosition());

    //Euler Rotations
    model_matrix = glm::rotate(model_matrix, attached_transform->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, attached_transform->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, attached_transform->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

    //Scale
    model_matrix = glm::scale(model_matrix, attached_transform->getScale());

    return model_matrix;
}

glm::mat4 Camera::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMatrix;
}