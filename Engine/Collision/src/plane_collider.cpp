PlaneCollider::PlaneCollider()
{

}

void PlaneCollider::init()
{
    plane = new btStaticPlaneShape(btVector3(0,1,0),0);
    motion = new btDefaultMotionState(transform);
    info = btRigidBody::btRigidBodyConstructionInfo((0.0, motion, plane);
    rigidbody = new btRigidBody(info);
    inertia = new btVector3(0,0,0);


}