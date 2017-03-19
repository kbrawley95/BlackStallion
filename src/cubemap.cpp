Cubemap::Cubemap(std::string texturePaths[], GLuint textureTargets[])
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    loadCubeMap(texturePaths, textureTargets);
    bindCubemapToPipeline(textureID);

}
bool Cubemap::loadCubeMap(std::string texturePaths[], GLuint textureTargets[])
{
    for(int i=0; i<texturePaths.size(); i++)
    {
        SDL_Surface* surfaceImage = IMG_Load(texturePaths[i].c_str());
        if(!imageSurface)
        {
            std::cout<<"Couldn't load specified texture: " <<texturePaths[i].c_str() <<std::endl;
            return false;
        }

        GLint noOfColours = surface->format->BytesPerPixel;

        GLenum textureFormat = GL_RGB;
        GLenum internalFormat = GL_RGB8;

        if(noOfColours == 4) //Contains an alpha channel
        {
            if(surface->format->Rmask == 0x000000ff)
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
            if(surface->format->Rmask == 0x000000ff)
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

        glTexImage2D(textureTargets[0] + i,  0, internalFormat, imageSurface->w, imageSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, imageSurface->pixels);

        SDL_FreeSurface(imageSurface);
    }

    return true;
  
    
}   

void Cubemap::bindCubemapToPipeline(GLuint textureID)
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  
}