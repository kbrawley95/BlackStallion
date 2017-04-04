#ifndef _COMMON_H
#define _COMMON_H

#ifdef __MINGW32__
#include <windows.h>
#endif

/*========STL========*/
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

/*========OPENGL========*/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

/*========SDL2========*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>

/*========TINY OBJ LOADER=======*/



/*========BULLET PHYSICS========*/
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

/*========GLM========*/
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/string_cast.hpp>
#include <GLM/gtc/constants.hpp>

/*========NAMESPACES========*/
// using namespace glm;
// using namespace std;
//using std::shared_ptr;

/*========PATHS========*/
const std::string ASSET_PATH  =  "assets";
const std::string SHADER_PATH = ASSET_PATH + "/shaders";
const std::string TEXTURE_PATH = ASSET_PATH + "/textures";
const std::string FONT_PATH = ASSET_PATH + "/fonts";    
const std::string MODEL_PATH = ASSET_PATH + "/models";
const std::string SOUND_PATH = ASSET_PATH + "/sound";

/*========CLASS HEADERS========*/

//Base
<<<<<<< HEAD:Engine/common.h
#include "Base/include/window.h"
#include "Base/include/vertex.h"
#include "Base/include/engine.h"
#include "Base/include/transform.h"
#include "Base/include/input.h"
#include "Base/include/component.h"
#include "Base/include/gameobject.h"
#include "Base/include/camera.h"
#include "Base/include/light.h"
#include "Base/include/scene.h"
#include "Base/include/shader.h"
// #include "Base/include/ui.h"

//Graphics
#include "Graphics/include/texture.h"
#include "Graphics/include/cube.h"
#include "Graphics/include/graphics.h"
#include "Graphics/include/skybox.h"
#include "Graphics/include/cubemap.h"

//Collision
#include "Collision/include/collision_manager.h"
#include "Collision/include/collider.h"
#include "Collision/include/plane_collider.h"
#include "Collision/include/box_collider.h"

//Model Loading
#include "Model Loading/include/objloader.h"

//Components
#include "Components/include/objmodel.h"
#include "Components/include/rigidbody.h"


=======
#include "window.h"
#include "vertex.h"
#include "engine.h"
#include "transform.h"
#include "input.h"
#include "camera.h"
#include "gameobject.h"
#include "shader.h"
#include "texture.h"
#include "ui.h"

//Collision
#include "../../Collision/include/collision_manager.h"
#include "../../Collision/include/collider.h"
#include "../../Collision/include/plane_collider.h"
#include "../../Collision/include/box_collider.h"
#include "../../Collision/include/rigidbody.h"

//Graphics
#include "../../Graphics/include/graphics.h"
#include "../../Graphics/include/cubemap.h"
#include "../../Graphics/include/cube.h"
#include "../../Graphics/include/skybox.h"

//Model Loading
#include "../../Model Loading/include/objloader.h"
#include "../../Model Loading/include/objStructure.h"
// #include "../../Model Loading/include/OBJLoader.h"
#include "../../Model Loading/include/objmodel.h"
>>>>>>> parent of 6c7ae85... Bullet Physics:Engine/Base/include/common.h


#endif