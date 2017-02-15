#include "../include/shader.h"

//Load shader from a memory buffer
GLuint Shader::loadShaderFromMemory(const char* pMem, SHADER_TYPE shaderType)
{
    GLuint programID = glCreateShader(shaderType);
    glShaderSource(programID, 1, &pMem, NULL);
    glCompileShader(program);
    return programID;
}

Gluint Shader::loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
    std::string fileContents;
    ifstream file;
    file.open(filename.c_str(), std::ios::in);
    if(!file)
    {
        std::cout<<"File could not be loaded"<<std::endl;
        return 0;
    }

    //Calculate file seize
    if(file.good())
    {
        file.seek(0, std::ios::end);
        unsigned long length=file.tellg();
        file.seekg(std::ios::beg);
        if(length==0)
        {
            std::cout<<"File has no contents"<<std::endl;
            return 0;
        }

        fileContents.resize(length);
        file.read(&fileContents[0], length);
        file.close();
        GLuint programID =loadShaderFromMemory(fileContents.c_str(),shaderType);
        return programID;
    }

    return 0;
}

bool Shader::checkForCompilerErrors(GLuint shaderProgam)
{
    GLint isCompiled =0;
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled==GL_FALSE)
    {
        GLint maxLength=0;
        glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength include the NULL character
        std::string infoLog;
        infoLog.resize(maxLength);
        glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

        std::cout<<"Shader not compiled"<<infoLog<<std::endl;

        //We don't need the shader anymore
        glDeleteShader(shaderProgram);
        return true;
    }

    return false;
}

bool Shader::checkForLinkErrors(GLuint program)
{
    GLint isCompiled =0;
    glGetProgram(program, GL_LINK_STATUS, &isCompiled);

    if(isLinked==GL_FALSE)
    {
        GLint maxLength=0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength include the NULL character
        std::string infoLog;
        infoLog.resize(maxLength);
        glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        std::cout<<"Shader not linked"<<infoLog<<std::endl;

        //We don't need the shader anymore
        glDeleteShader(program);
        return true;
    }
    

    return false;
}

