void Input::checkForControllers()
{ 
    SDL_GameController* controller = nullptr;

    for(int i=0; i<SDL_NumJoysticks(); i++)
    {
        if(SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            if (controller)
            {
                printf("Controller Found: %s\n", SDL_GameControllerName(controller));
            } 
            break;
        }
    }

}

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
                    //std::cout << "Mouse = (" << xPos << ", " << yPos << ")" << std::endl;
                }
                else
                    inbounds = false;
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                buttons[event.cbutton.button]=true;
                break;

            case SDL_CONTROLLERBUTTONUP:
                buttons[event.cbutton.button]=false;
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