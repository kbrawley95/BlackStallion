#ifndef _AUDIO_MANAGER_H
#define _AUDIO_MANAGER_H

class AudioManager
{
    public:
        AudioManager();
        ~AudioManager();

        void init();
        void play();
        void pause();
        void stop();

    private:
        ALCdevice* alDevice;
};

#include "../src/audio_manager.cpp"

#endif