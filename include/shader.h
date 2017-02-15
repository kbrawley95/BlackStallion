#ifndef _SHADER_H
#define _SHADER_H

#include "Common.h"

class Shader
{
    public:
    enum SHADER_TYPE
    {
        VERTEX_SHADER=GL_VERTEX_SHADER;
        FRAGMENT_SHADER=GL_FRAGMENT_SHADER;
    }

    GLuint loadShaderFromMemory(const char* pMem, SHADER_TYPE shaderType);
    Gluint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType);

    bool checkForCompilerErrors(GLuint shaderProgam);
    bool checkForLinkErrors(GLuint program);


};


#endif 

