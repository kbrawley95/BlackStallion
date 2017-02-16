#include "../include/shader.h"

//Load shader from a memory buffer
GLuint Shader::loadShaderFromMemory(const char* pMem, SHADER_TYPE shaderType)
{
    GLuint program= glCreateShader(shaderType);
    glShaderSource(program, 1, &pMem, NULL);
    glCompileShader(program);
    return program;
}

GLuint Shader::loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
    std::string fileContents;
    ifstream file;
    file.open(filename.c_str(), std::ios::in);
    if(!file)
    {
        std::cout<<"File: " << filename.c_str() << " could not be loaded"<<std::endl;
        return 0;
    }

    //Calculate file seize
    if(file.good())
    {
        file.seekg(0, std::ios::end);
        unsigned long length=file.tellg();
        file.seekg(std::ios::beg);
        if(length==0)
        {
            std::cout<<"File: "  <<filename.c_str() <<" has no contents"<<std::endl;
            return 0;
        }

        fileContents.resize(length);
        file.read(&fileContents[0], length);
        file.close();
        
        GLuint program =loadShaderFromMemory(fileContents.c_str(),shaderType);
        return program;
    }


    return 0;
}

bool Shader::checkForCompilerErrors(GLuint shaderProgram)
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
    GLint isLinked=0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

    if(isLinked==GL_FALSE)
    {
        GLint maxLength=0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength include the NULL character
        std::string infoLog;
        infoLog.resize(maxLength);
        glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        std::cout<<"Shader not linked"<<infoLog<<std::endl;

        //We don't need the shader anymore
        glDeleteProgram(program);
        return true;
    }
    

    return false;
}

void Shader::installShaders(const std::string vertexShader, const std::string fragmentShader)
{
    GLuint vertexShaderProgram=0;
    string vsPath = SHADER_PATH + vertexShader;
    vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
    checkForCompilerErrors(vertexShaderProgram);

    GLuint fragmentShaderProgram=0;
    string fsPath = SHADER_PATH + fragmentShader;
    fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
    checkForCompilerErrors(fragmentShaderProgram);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderProgram);
    glAttachShader(shaderProgram, fragmentShaderProgram);

    glBindAttribLocation(shaderProgram, 0, "vertexPosition");
    
    glLinkProgram(shaderProgram);
    checkForLinkErrors(shaderProgram);

    //Now we ccan delete the VS & FS Programs
    glDeleteShader(vertexShaderProgram);
    glDeleteShader(fragmentShaderProgram);
}

