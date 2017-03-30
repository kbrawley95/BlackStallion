
Transform::Transform()
{
    position = glm::vec3(0.0f,0.0f, 0.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    model_matrix = glm::mat4x4(1.0f);

    createModelToWorldMatrix();

    front = glm::vec3(model_matrix[2][0], model_matrix[2][1], model_matrix[2][2]);

    pitch = 0.0f;
    yaw = 0.0f;
}

Transform::~Transform()
{
    
}

void Transform::createModelToWorldMatrix()
{
   //Translation
    glm::mat4 model_pos = glm::translate(glm::mat4(1.0f), position);

    //Euler Rotations
    glm::mat4 model_rot = glm::mat4(1.0f);
    model_rot = glm::rotate(model_rot, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_rot = glm::rotate(model_rot, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model_rot = glm::rotate(model_rot, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    //Scale
    glm::mat4 model_size = glm::scale(glm::mat4(1.0f), scale);
    model_matrix = model_size * model_rot * model_pos;

}

glm::mat4x4 Transform::getModelToWorldMatrix()
{
    return model_matrix;
}


glm::vec3 Transform::forward()
{
    //front = glm::vec3(model_matrix[2][0], model_matrix[2][1], model_matrix[2][2]);
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

void Transform::setForward(glm::vec3 newDirection)
{
    front = newDirection;
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
   createModelToWorldMatrix();
}

void Transform::setRotation(glm::vec3 newRot)
{
   rotation+=newRot;

   createModelToWorldMatrix();
}


void Transform::setScale(float scalar)
{
   scale.x *= scalar;
   scale.y *= scalar;
   scale.z *= scalar;
   createModelToWorldMatrix();
}
