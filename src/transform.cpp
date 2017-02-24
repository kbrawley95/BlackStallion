
Transform::Transform()
{
    position = glm::vec3(0.0f,0.0f,-10.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    
}

Transform::~Transform()
{
    
}



glm::vec3 Transform::forward()
{
    // return glm::vec3(getModeltoWorldMatrix()[2][0],getModeltoWorldMatrix()[2][1],getModeltoWorldMatrix()[2][2]);
    return glm::vec3(0.0f,0.0f,1.0f);
}

glm::vec3 Transform::up()
{
    // return glm::vec3(getModeltoWorldMatrix()[1][0],getModeltoWorldMatrix()[1][1],getModeltoWorldMatrix()[1][2]);
    return glm::vec3(0.0f,1.0f,0.0f);
    
}

glm::vec3 Transform::right()
{
    // return glm::vec3(getModeltoWorldMatrix()[0][0],getModeltoWorldMatrix()[0][1],getModeltoWorldMatrix()[0][2]);
    return glm::vec3(1.0f,0.0f,0.0f);
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

