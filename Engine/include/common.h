#ifndef _COMMON_H
#define _COMMON_H

#ifdef __MINGW32__
#include <windows.h>
#endif

//GENERAL
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <list>
#include <map>
#include <algorithm>

//OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>

//BULLET
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

//MATHS
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/string_cast.hpp>
#include <GLM/gtc/constants.hpp>

//NAMESPACES
// using namespace glm;
// using namespace std;
using std::shared_ptr;

//PATHS
const std::string ASSET_PATH  =  "assets";
const std::string SHADER_PATH = ASSET_PATH + "/shaders";
const std::string TEXTURE_PATH = ASSET_PATH + "/textures";
const std::string FONT_PATH = ASSET_PATH + "/fonts";    
const std::string MODEL_PATH = ASSET_PATH + "/models";
const std::string SOUND_PATH = ASSET_PATH + "/sound";

//CLASS HEADERS
#include "engine.h"
#include "window.h"
#include "vertex.h"
#include "graphics.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "input.h"
#include "camera.h"
#include "cube.h"
#include "cubemap.h"
#include "gameobject.h"
#include "skybox.h"
#include "objloader.h"
#include "objmodel.h"
#include "ui.h"

#include "../Collision/include/collision_manager.h"
#include "../Collision/include/collider.h"
#include "../Collision/include/plane_collider.h"
#include "../Collision/include/box_collider.h"

#endif