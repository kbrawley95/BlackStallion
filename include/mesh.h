#ifndef _MESH_H
#define _MESH_H

class Mesh : public GameObject
{
    public:
        Mesh(std::string name, std::string filepath, std::string texturepath);

        void loadModel(std::string filepath);
        void assignMeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void init();
        void render(Camera* mainCamera);
        void cleanUp();

    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        Model* model;
        GLuint vertexArrayID;
        GLuint vertexBufferID;
        GLuint elementBufferID;

        Shader* textureShader;
        GLuint textureID;
        Texture* texture;
};

#include "../src/mesh.cpp"

#endif