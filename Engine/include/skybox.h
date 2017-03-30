#ifndef _SKYBOX_H
#define _SKYBOX_H

class Skybox : public GameObject
{
    public:
        Skybox(std::string name);
        void initSkybox();
        GLuint generateCubeMap();
        void render(Camera* mainCamera);
        void cleanUp();

    private:
        //Buffer objects
        GLuint vertexArrayID;
        GLuint vertexBufferID;
        GLuint elementsBufferID;

        Shader* skyboxShader;

        Cubemap* cubemap;
        GLuint cubemapTextureID;

  
    std::vector<std::string>texturePaths;
    std::vector<GLenum>textureTargets;
    
};

#include "../src/skybox.cpp"

#endif