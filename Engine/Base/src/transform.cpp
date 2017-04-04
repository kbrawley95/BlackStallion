
Transform::Transform()
{
    position = glm::vec3(0.0f,0.0f, 0.0f);
    rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    createModelToWorldMatrix();
}

Transform::~Transform()
{
    
}

void Transform::createModelToWorldMatrix()
{
   //Translation
    glm::mat4 model_pos = glm::translate(glm::mat4(1.0f), position);

    //Euler Rotations
    glm::mat4x4 model_rot = glm::mat4(rotation);

    //Scale
    glm::mat4 model_scale = glm::scale(glm::mat4(1.0f), scale);

    model_matrix = model_scale * model_rot * model_pos;
}

glm::mat4x4 Transform::getModelToWorldMatrix()
{
    return model_matrix;
}


glm::vec3 Transform::forward()
{
    front = glm::vec3(model_matrix[2][0], model_matrix[2][1], model_matrix[2][2]);
    return front;
}

glm::vec3 Transform::up()
{
    glm::vec3 up = glm::vec3(model_matrix[1][0], model_matrix[1][1], model_matrix[1][2]);
    return up;
}

glm::vec3 Transform::right()
{
    glm::vec3 right = glm::vec3(model_matrix[0][0], model_matrix[0][1], model_matrix[0][2]);
    return right;
}

//GETTERS

glm::vec3 Transform::getPosition()
{
   return position;
}

glm::quat Transform::getRotation()
{
   return rotation;
}

glm::vec3 Transform::getScale()
{
   return scale;
}

//SETTERS
void Transform::setPosition(glm::vec3 newPos)
{
   position = newPos;
   createModelToWorldMatrix();
}

void Transform::setRotation(glm::quat newRot)
{
   rotation = newRot;
   createModelToWorldMatrix();
}

void Transform::setScale(glm::vec3 newScale)
{
    scale = newScale;
   
   createModelToWorldMatrix();
}

void Transform::rotate(glm::vec3 newRot)
{
    glm::quat pitch     = glm::angleAxis(newRot.x, glm::vec3(1, 0, 0));
    glm::quat yaw       = glm::angleAxis(newRot.y, glm::vec3(0, 1, 0));
    glm::quat roll      = glm::angleAxis(newRot.z, glm::vec3(0, 0, 1));
    
    rotation            = yaw * pitch * roll;
    createModelToWorldMatrix();
}



