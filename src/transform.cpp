
Transform::Transform()
{
    position = glm::vec3(0.0f,0.0f, 3.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    pitch = 0.0f;
    yaw = 0.0f;
}

Transform::~Transform()
{
    
}

glm::mat4x4 Transform::getModeltoWorldMatrix()
{
    glm::mat4x4 model_matrix = glm::mat4x4(1.0f);
    
    //Translation
    model_matrix = glm::translate(model_matrix, position);

    //Euler Rotations
    model_matrix = glm::rotate(model_matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    //Scale
    model_matrix = glm::scale(model_matrix, scale);

    return model_matrix;
}



glm::vec3 Transform::forward()
{
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(position - cameraTarget);
    front = cameraDirection;
    return front;
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
void Transform::setPosition(glm::vec3 newPos)
{
   position+=newPos;
}

void Transform::lookHorizontal(float yaw)
{
   rotation.y += sin(glm::radians(yaw));
   
}

void Transform::lookVertical(float pitch)
{
   rotation.x += cos(glm::radians(pitch));
   rotation.z += sin(glm::radians(pitch));
   
}


void Transform::setPitch(float angle)
{
    pitch = glm::radians(angle);
}

void Transform::setYaw(float angle)
{
    yaw = glm::radians(angle);
}

