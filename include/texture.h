#ifndef _TEXTURE
#define _TEXTURE

class Texture
{
    public:
    GLuint loadTextureFromFile(const std::string& filename);
    GLuint convertSDLSurfaceToTexture(SDL_Surface* surface);
};

#include "../src/texture.cpp"

#endif 