#ifndef _LIGHT_H
#define _LIGHT_H

class Light
{
    public:
        Light();
        ~Light();

        glm::vec3 getPosition();
        glm::vec4 getColour();

    private:
        glm::vec3 position;
        glm::vec3 colour;
};

#endif