#ifndef _INPUT_H
#define _INPUT_H

class Input
{
    public:
        static bool update(SDL_Event event);
        //Keyboard Input Map
        static std::map<int, bool>keys;

        //Mouse Input
        static std::map<int, bool>mouse;
        
        static glm::vec2 mouseDelta;
        static glm::vec2 mousePosition;
        static int xPos, yPos;

    private:

        //Mouse Coordinates
        static bool inbounds;
        static bool isRunning;

};

//Instantiate to avoid reference error
std::map<int, bool> Input::keys;

glm::vec2 Input::mouseDelta;
glm::vec2 Input::mousePosition;
int Input::xPos,Input:: yPos;
bool Input::inbounds;
bool Input::isRunning;

#include "../src/input.cpp"

#endif