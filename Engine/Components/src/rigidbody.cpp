Rigidbody::Rigidbody(Collider* newCollider, glm::vec3 relativePosition, glm::quat relativeRotation, glm::vec3 relativeScale)
{
    position = btVector3(relativePosition.x,relativePosition.y,relativePosition.z);
    rotation = btQuaternion(relativeRotation.x, relativeRotation.y, relativeRotation.z, relativeRotation.w);
  
    //Transform realtive to Gameobject associated with
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(position);
    transform.setRotation(rotation);
    
    //Inertia is the resistance to change in state of motion
    btVector3 inertia = btVector3(0, 0, 0);
    //Initialise Collider associated with rigidbody
    collider = newCollider;
    motion = new btDefaultMotionState(transform);
    
    //If the mass is no 0, then the object is dynamic
    if(mass!=0.0)
        collider->getShape()->calculateLocalInertia(mass, inertia);
        
    btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(mass, motion, collider->getShape(), inertia);
    rigidbody = new btRigidBody(info);

    //At rigidbody to world
    CollisionManager::getWorld()->addRigidBody(rigidbody);
    CollisionManager::addRigidbodyToList(rigidbody);
}

Rigidbody::~Rigidbody()
{
    delete motion;
    delete rigidbody;
    delete collider;
}

btRigidBody* Rigidbody::getRigidbody()
{
    return rigidbody;
}

btMotionState* Rigidbody::getMotion()
{
    return motion;
}

void Rigidbody::update()
{
    if(mass != 0.0f)
    {
        if(motion != NULL)
        {
            btTransform transform;
            motion->getWorldTransform(transform);
            glm::mat4x4 world_matrix;
            transform.getOpenGLMatrix(glm::value_ptr(world_matrix));
            gameObject->getTransform()->setModelToWorldMatrix(world_matrix);
        }
    }
}