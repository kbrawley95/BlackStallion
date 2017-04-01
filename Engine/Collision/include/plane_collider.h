#ifndef _PLANE_COLLIDER_H
#define _PLANE_COLLIDER_H

class PlaneCollider : public Collider
{
    public:
        PlaneCollider();
        void init();

    private:
        btStaticPlaneShape* plane;
};

#include "../src/plane_collider.cpp"

#endif 