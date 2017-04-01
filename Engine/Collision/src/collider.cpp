Collider::Collider()
{
    init();
}

void Collider::init()
{
    transform = new btTransform();
    transform->setIdentity();
    transform->setOrigin(btVector3(0,0,0));
}