#ifndef _PLANE_H
#define _PLANE_H

class Plane 
{
    public:
        static std::vector<Vertex> m_vertices;
        static std::vector<GLuint> m_indices;
};

std::vector<Vertex> Cube::m_vertices = 
{
    /*FRONT*/
    //Position                    //Colour                           //Texture Coordinates
    {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3(0.5f, -0.5f 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3(0.5f, 0.5f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

    /*BACK*/
    //Position                      //Colour                          //Texture Coordinates
    {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3(0.5f, -0.5f -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3(0.5f, 0.5f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
};

std::vector<GLuint> Cube::m_indices = {
    
    // front
    0, 1, 2,
    2, 3, 0,

    // back
    7, 6, 5,
    5, 4, 7,

    // top
    1, 5, 6,
    6, 2, 1,

    // bottom
    4, 0, 3,
    3, 7, 4,

    // left
    4, 5, 1,
    1, 0, 4,
    
    // right
    3, 2, 6,
    6, 7, 3,
};

#endif 