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

void CollisionManager::cleanUp()
{
    delete collisionConfig;
    delete dispatcher;
    delete broadphase;
    delete world;
}
   