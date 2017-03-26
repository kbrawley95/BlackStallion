
Transform::Transform()
{
    position = glm::vec3(0.0f,0.0f, 0.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    model_matrix = glm::mat4x4(1.0f);

    createModelToWorldMatrix();
    

    pitch = 0.0f;
    yaw = 0.0f;
}

Transform::~Transform()
{
    
}

void Transform::createModelToWorldMatrix()
{
    //Translation
    model_matrix = glm::translate(model_matrix, position);

    //Euler Rotations
    model_matrix = glm::rotate(model_matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    //Scale
    model_matrix = glm::scale(model_matrix, scale);
}

glm::mat4x4 Transform::getModelToWorldMatrix()
{
    return model_matrix;
}


glm::vec3 Transform::forward()
{
    glm::vec3 front = glm::vec3(model_matrix[2][0], model_matrix[2][1], model_matrix[2][2]);
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
   position=newPos;
   createModelToWorldMatrix();
}

void Transform::setRotation(glm::vec3 newRot)
{
   rotation.x=newRot.x;
   rotation.y=newRot.y;
   rotation.z=newRot.z;

   createModelToWorldMatrix();
}


void Transform::setScale(float scalar)
{
   scale.x *= scalar;
   scale.y *= scalar;
   scale.z *= scalar;
   createModelToWorldMatrix();
}
