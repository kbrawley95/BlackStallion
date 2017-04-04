#ifndef _OBJMODEL_H
#define _OBJMODEL_H

class OBJModel : public Component
{
    public:
        OBJModel(std::string name, const char* path, std::string texturepath);

        void init();
        void render(Camera* renderer);
        void cleanUp();
        
    private:
        Shader* modelShader = NULL;
        GLuint textureID = 0;
        Texture* texture = NULL;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        GLuint VBO = 0;
        GLuint EBO = 0;
        GLuint VAO = 0;
        
};

#include "../src/objmodel.cpp"

#endif