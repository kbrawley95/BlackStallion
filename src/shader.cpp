#include "../include/shader.h"

Shader::Shader(const std::string vertexShader, const std::string fragmentShader)
{
    shaderProgram = 0;

    GLuint vertexShaderProgram=0;
    std::string vsPath = SHADER_PATH + vertexShader;
    vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
    checkForCompilerErrors(vertexShaderProgram);

    GLuint fragmentShaderProgram=0;
    std::string fsPath = SHADER_PATH + fragmentShader;
    fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
    checkForCompilerErrors(fragmentShaderProgram);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShaderProgram);
    glAttachShader(shaderProgram, fragmentShaderProgram);

    glBindAttribLocation(shaderProgram, 0, "vertexPosition");
    glBindAttribLocation(shaderProgram, 1, "vertexColour");
    
    glLinkProgram(shaderProgram);
    checkForLinkErrors(shaderProgram);

    //Now we can delete the VS & FS Programs
    glDeleteShader(vertexShaderProgram);
    glDeleteShader(fragmentShaderProgram);
}

Shader::~Shader()
{
     
}

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
    std::ifstream openfile;
    openfile.open(filename);

    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            openfile.seekg(0, std::ios::end);
            unsigned long length=openfile.tellg();
            openfile.seekg(std::ios::beg);
            if(length==0)
            {
                std::cout<<"File: "  <<filename.c_str() <<" has no contents"<<std::endl;
                return 0;
            }

            fileContents.resize(length);
            openfile.read(&fileContents[0], length);
            openfile.close();

            //std::cout<<"File Contents: " <<fileContents<<std::endl;
            
            GLuint program =loadShaderFromMemory(fileContents.c_str(),shaderType);
            std::cout<<"Shader: "<< filename.c_str() + 15<<" loaded successfully."<<std::endl;
            return program;
        }

    }
    else
    {
        std::cout<<"Could not open file"<<std::endl;
        return 0;
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

GLuint Shader::getShaderProgram()
{
    return shaderProgram;
}

