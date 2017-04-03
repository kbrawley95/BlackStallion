#ifndef _SKYBOX_H
#define _SKYBOX_H

class Cubemap : public Component
{
    public:
        Cubemap();
        GLuint generateCubeMap();

        void init();
        void render(Camera* mainCamera);
        void cleanUp();
        
        Skybox* cubemap;
       
    private:
        //Buffer objects
        GLuint vertexArrayID;
        GLuint vertexBufferID;
        GLuint elementsBufferID;

        Shader* skyboxShader;

        GLuint cubemapTextureID;

        std::vector<glm::vec3> vertices;

  
    std::vector<std::string>texturePaths;
    std::vector<GLenum>textureTargets;
    
};

#include "../src/cubemap.cpp"

#endif