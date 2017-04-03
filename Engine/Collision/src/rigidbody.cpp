Rigidbody::Rigidbody(Collider* newCollider, float newMass,
glm::vec3 relativePosition, glm::quat relativeRotation, glm::vec3 relativeScale)
{
    position = btVector3(relativePosition.x,relativePosition.y,relativePosition.z);
    rotation = btQuaternion(relativeRotation.x, relativeRotation.y, relativeRotation.z, relativeRotation.w);

  
    //Initialise Transform
    transform.setIdentity();
    transform.setOrigin(position);
    transform.setRotation(rotation);
    
    //Initialise Collider associated with rigidbody
    collider = newCollider;
    mass = newMass;
    motion = new btDefaultMotionState(transform);
    inertia = btVector3(0, 0, 0);
    
    //If the mass is no 0, then the object is dynamic
    if(mass!=0)
        collider->getShape()->calculateLocalInertia(mass, inertia);
        
    btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(mass, motion, collider->getShape(), inertia);
    rigidbody = new btRigidBody(info);

    //At rigidbody to world
    CollisionManager::addRigidBodyToWorld(rigidbody);

}

Rigidbody::~Rigidbody()
{
    delete motion;
    delete rigidbody;
    delete collider;
}

btTransform Rigidbody::getTransform()
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


btVector3 Rigidbody::getInertia()
{
    return inertia;
}