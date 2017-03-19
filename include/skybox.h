#ifndef _SKYBOX_H
#define _SKYBOX_H

class Skybox
{
    public:

        Skybox(const Camera* mainCamera, const )

        virtual bool initSkybox();

        void setWorldViewProjection();
        void setTextureUnit(unsigned int textureUnit);


    private:
        GLuint m_WVPLocation;
        GLuint m_textureLocation;
};

#include "../src/skybox.cpp"

#endif