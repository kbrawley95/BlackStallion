Collider::Collider()
{
    init();
}

btTransform* Collider::getTransform()
{
    return transform;
}

btMotionState* Collider::getMotion()
{
    return motion;
}

btRigidBody* Collider::getRigidbody()
{
    return rigidbody;
}

btRigidBody::btRigidBodyConstructionInfo* Collider::getInfo()
{
    return info;
}

btVector3* Collider::getInertia()
{
    return inertia;
}

void Collider::init()
{
    transform = new btTransform();
    transform->setIdentity();
    transform->setOrigin(btVector3(0,0,0));
}