#ifndef _INPUT_H
#define _INPUT_H

class Input
{
    public:
    //Keyboard Input Map
    static std::map<int, bool>keys;
    static std::map<int, bool>mouse;

};

//Instantiate to avoid reference error
std::map<int, bool> Input::keys;

#endif