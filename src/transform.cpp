
Transform::Transform()
{
    position = glm::vec3(0.0f,0.0f, 10.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    
}

Transform::~Transform()
{
    
}

glm::mat4x4 Transform::getModeltoWorldMatrix()
{
    glm::mat4x4 model_matrix = glm::mat4x4(1.0f);
    
    //Translation
    model_matrix = glm::translate(model_matrix, getPosition());

    //Euler Rotations
    model_matrix = glm::rotate(model_matrix, getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

    //Scale
    model_matrix = glm::scale(model_matrix, getScale());

    return model_matrix;
}



glm::vec3 Transform::forward()
{
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(position - cameraTarget);
    return cameraDirection;
    
}

glm::vec3 Transform::up()
{
    glm::vec3 up = glm::cross(forward(), right());
    return up;
}

glm::vec3 Transform::right()
{
    glm::vec3 up = glm::vec3(0.0f,1.0f, 0.0f);
    glm::vec3 cameraRight=glm::normalize(glm::cross(up, forward())); 
    return cameraRight;
}

//GETTERS

glm::vec3 Transform::getPosition()
{
   return position;
}

glm::vec3 Transform::getScale()
{
   return scale;
}

glm::vec3 Transform::getRotation()
{
   return rotation;
}


//SETTERS
glm::vec3 Transform::setPosition(glm::vec3 newPos)
{
   position+=newPos;
}

glm::vec3 Transform::setScale(glm::vec3 newScale)
{
   scale+=newScale;
}

glm::vec3 Transform::setRotation(glm::vec3 newRotation)
{
   rotation += newRotation * ToRadians(45.0f);
}

