#ifndef _PLANE_COLLIDER_H
#define _PLANE_COLLIDER_H

class PlaneCollider : public Collider
{
    public:
        PlaneCollider(glm::vec3 position, float scale)
        {
            plane = new btStaticPlaneShape(btVector3(position.x, position.y, position.z), btScalar(scale));
        }

        ~PlaneCollider()
        {   
            delete plane;
        }

    private:
        btStaticPlaneShape* plane;
};

#endif 