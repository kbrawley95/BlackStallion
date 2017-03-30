bool Input::update(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                keys[event.key.keysym.sym]=true;
                break;

            case SDL_KEYUP:
               keys[event.key.keysym.sym]=false;
                break;
            
            case SDL_MOUSEMOTION:
                 xPos=event.button.x;
                 yPos=event.button.y;

                if(xPos > 0 && xPos < (Window::WIDTH - 1))
                {
                    inbounds = true;
                    std::cout << "Mouse = (" << xPos << ", " << yPos << ")" << std::endl;
                }
                else
                    inbounds = false;
                break;

            case SDL_QUIT:
                isRunning=false;
                break;
            case SDL_WINDOWEVENT_CLOSE:
              isRunning=false;
                break;
        }
    }

    return true;
}