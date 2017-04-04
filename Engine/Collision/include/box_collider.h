#ifndef _BOX_COLLIDER_H
#define _BOX_COLLIDER_H

class BoxCollider : public Collider
{
    public:
        BoxCollider(glm::vec3 position) 
        {
            box = new btBoxShape(btVector3(position.x, position.y, position.z));
        }

        ~BoxCollider()
        {
            delete box;
        }


    private:
        btBoxShape* box;
};


#endif
