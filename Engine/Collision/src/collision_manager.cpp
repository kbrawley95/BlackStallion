CollisionManager::CollisionManager()
{
    init();
}

void CollisionManager::init()
{
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();

    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
    world->setGravity(btVector3(0, -9.82f, 0));
}

void CollisionManager::update(float &deltaTime)
{
     world->stepSimulation(deltaTime);
}

void CollisionManager::cleanUp()
{
    delete collisionConfig;
    delete dispatcher;
    delete broadphase;
    delete world;
}

void CollisionManager::addRigidBodyToWorld(btRigidBody* body)
{
    world->addRigidBody(body);
    rigidBodies.push_back(body);
}
   