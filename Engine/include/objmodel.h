#ifndef _OBJMODEL_H
#define _OBJMODEL_H

class OBJModel : GameObject
{
    public:
        OBJModel(std::string name, const char* path, std::string texturepath);

        void init();
        void render(Camera* mainCamera);
        
    private:
        // Read our .obj file
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals; // Won't be used at the moment.

        OBJLoader* objLoader;
        GLuint vertexArrayID, vertexBufferID;

        Shader* modelShader;
        GLuint textureID;
        Texture* texture;

        std::vector<Vertex> m_vertices;
};

#include "../src/objmodel.cpp"

#endif