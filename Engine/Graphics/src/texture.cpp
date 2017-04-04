GLuint Texture::loadTextureFromFile(const std::string& filename)
{
    SDL_Surface* imageSurface = IMG_Load(filename.c_str());
    if(!imageSurface)
    {
        std::cout<<"Can't load image: " << filename <<" " <<IMG_GetError() <<std::endl;
        return 0;
    }

    GLuint textureID = convertSDLSurfaceToTexture(imageSurface);
    SDL_FreeSurface(imageSurface);
    bindTextureToPipeLine(textureID);

    std::cout<<"Image: " << filename <<" loaded successfully." << std::endl;

    return textureID;

}

 
void Texture::bindTextureToPipeLine(GLuint textureID)
{
    glBindTexture(GL_TEXTURE_2D, textureID); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);

}


GLuint Texture::loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text)
{
    TTF_Font * font = TTF_OpenFont(fontFilename.c_str(), pointSize);
    if(!font)
    {
        std::cout<<"Unable to load font " <<fontFilename << " " <<TTF_GetError()<<std::endl;
        return 0;
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(),
        {255,255,255});

    GLuint textureID = convertSDLSurfaceToTexture(textSurface);
    SDL_FreeSurface(textSurface);

    TTF_CloseFont(font);

        
    return textureID;
}

GLuint Texture::convertSDLSurfaceToTexture(SDL_Surface* surface)
{
    GLuint textureID = 0;
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

    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, 
        textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

    return textureID;
}

