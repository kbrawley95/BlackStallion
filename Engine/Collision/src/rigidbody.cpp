Rigidbody::Rigidbody(float newMass, glm::vec3 resistance, glm::vec3 relativePosition, glm::quat relativeRotation, glm::vec3 relativeScale)
{
    position = btVector3(relativePosition.x,relativePosition.y,relativePosition.z);
    rotation = btQuaternion(relativeRotation.x, relativeRotation.y, relativeRotation.z, relativeRotation.w);
  
    //Initialise Transform
    transform = new btTransform();
    transform->setIdentity();
    transform->setOrigin(position);
    transform->setRotation(rotation);
    
    //Initialise Collider associated with rigidbody
    collider = new Collider();
    mass = newMass;
    motion = new btDefaultMotionState(transform);
    inertia = new btVector3(resistance.x, resistance.y, resistance.z);
    info = btRigidBody::btRigidBodyConstructionInfo(mass, motion, collider->getShape(), inertia);
    rigidbody = new btRigidBody(info);

    //If the mass is no 0, then the object is dynamic
    if(mass!=0.0)
        calculateLocalInertia(mass, inertia);
}

Rigidbody::~Rigidbody()
{
    delete rigidbody;
    delete transform;
    delete motion;
    delete inertia;
}

btTransform* Rigidbody::getTransform()
{
    return transform;
}

btMotionState* Rigidbody::getMotion()
{
    return motion;
}

btRigidBody* Rigidbody::getRigidbody()
{
    return rigidbody;
}

btRigidBody::btRigidBodyConstructionInfo* Collider::getInfo()
{
    return info;
}

btVector3* Rigidbody::getInertia()
{
    return inertia;
}