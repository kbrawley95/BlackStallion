Cubemap::Cubemap(std::vector<std::string>texturePaths, std::vector<GLenum>textureTargets)
{
    textureID = loadCubeMap(texturePaths, textureTargets);
    bindCubemapToPipeline(textureID);
}

GLuint Cubemap::getTextureID()
{
    return textureID;
}

GLuint Cubemap::loadCubeMap(std::vector<std::string>texturePaths, std::vector<GLenum>textureTargets)
{
    std::cout<<std::endl;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    for(int i=0; i<texturePaths.size(); i++)
    {
        SDL_Surface* surfaceImage = IMG_Load(texturePaths[i].c_str());
        
        if(!surfaceImage)
        {
            std::cout<<"Couldn't load specified texture: " <<texturePaths[i].c_str() <<std::endl;
            return 0;
        }

        GLint noOfColours = surfaceImage->format->BytesPerPixel;

        GLenum textureFormat = GL_RGB;
        GLenum internalFormat = GL_RGB8;

        if(noOfColours == 4) //Contains an alpha channel
        {
            if(surfaceImage->format->Rmask == 0x000000ff)
            {
                textureFormat = GL_RGBA;
                internalFormat = GL_RGBA8;
            }
            else
            {
                textureFormat = GL_BGRA;
                internalFormat = GL_RGBA8;
            }
        }
        else if (noOfColours == 3) //no alpha channel
        {
            if(surfaceImage->format->Rmask == 0x000000ff)
            {
                textureFormat = GL_RGB;
                internalFormat = GL_RGB8;
            }
            else
            {
                textureFormat = GL_BGR;
                internalFormat = GL_RGB8;
            }
        }
        else
        {
            std::cout<<"Warning: The image is not truecolour";
            return 0;
        }

        glTexImage2D(textureTargets[0] + i,  0, internalFormat, surfaceImage->w, surfaceImage->h, 0, textureFormat, GL_UNSIGNED_BYTE, surfaceImage->pixels);

        SDL_FreeSurface(surfaceImage);
        std::cout<<"Texture: " <<texturePaths[i].c_str() <<" successfully loaded." <<std::endl;
        
        
    }

    return textureID;
}   

void Cubemap::bindCubemapToPipeline(GLuint textureID)
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  
}