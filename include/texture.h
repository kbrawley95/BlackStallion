#ifndef _TEXTURE
#define _TEXTURE

class Texture
{
    public:
    GLuint loadTextureFromFile(const std::string& filename);
    GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text);
    GLuint convertSDLSurfaceToTexture(SDL_Surface* surface);
};

#include "../src/texture.cpp"

#endif 