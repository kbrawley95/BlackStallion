#ifndef _UI_H
#define _UI_H

class UI : public GameObject
{
    public:
        UI(std::string name, std::string filepath, int fontSize, std::string caption);
        void init();
        void render(Camera* mainCamera);
        void cleanUp();

    private:
        Texture* texture;
        GLuint textureID;

        Shader* uiShader;

        GLuint vertexArrayID;
        GLuint vertexBufferID;

        std::vector<Vertex>m_vertices;

};

#include "../src/ui.cpp"
#endif