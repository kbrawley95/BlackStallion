  Cubemap::Cubemap(const string& directory,const std::string& posX,const std::string& negX,const std::string& posY, 
  const std::string& negY,const std::string& posZ,const std::string& negZ)
  {
    m_fileNames.push_back(&posX);
    m_fileNames.push_back(&negX);
    m_fileNames.push_back(&posY);
    m_fileNames.push_back(&negX);
    m_fileNames.push_back(&posZ);
    m_fileNames.push_back(&negZ);
  }

  bool Cubemap::loadCubemap()
  {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

    for(int = 0; i<m_fileNames.size(); i++)
    {
        SDL_Surface* imageSurface = IMG_LOAD(TEXTURE_PATH + m_fileNames[i]);
        if(!imageSurface)
        {
            std::cout<<"Couldn't load specified image: "<<m_fileNames[i] <<std::endl;
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
            return false;
        }

        glTexImage2D(m_cubeMapFaceTypes[i], 0, internalFormat, imageSurface->w, imageSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, imageSurface->pixels);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        SDL_FreeSurface(imageSurface);
            
    }

    return true;
    
  }

  void Cubemap::bindCubemapToPipeline(GLenum textureUnit)
  {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
  }