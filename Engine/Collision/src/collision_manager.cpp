CollisionManager::CollisionManager()
{
    init();
}

void CollisionManager::init()
{
    std::cout<<"\nInitialising Collision Manager..."<<std::endl;
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();

    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
    world->setGravity(btVector3(0, -9.82f, 0));
    std::cout<<"\nInitialisation Succesful\n"<<std::endl;
}

void CollisionManager::update(float &deltaTime)
{
     world->stepSimulation(deltaTime);
}

void CollisionManager::cleanUp()
{
    delete broadphase;
    delete collisionConfig;
    delete dispatcher;
    delete world;
}

void CollisionManager::addRigidBodyToWorld(btRigidBody* newRigidbody)
{
    world->addRigidBody(newRigidbody);
    rigidBodies.push_back(newRigidbody);
}

btDynamicsWorld* CollisionManager::getWorld()
{
    return world;
}
   