#include <stdio.h>

#include "SDLLightGUI.h"

int main(int args, char** arg)
{
    std::string title = "Light GUI Demo";
    LGUI::Window window(title, 1000, 1000);
    /*
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // the rect color (solid red)
        SDL_Rect rect; // the rectangle
        rect.x = 0;
        rect.y = 0;
        rect.w = 100;
        rect.h = 50;
        SDL_RenderFillRect(renderer, &rect);


        SDL_RenderPresent(renderer); // copy to screen
    */

    window.addComponent(new LGUI::Button(100,50,50,30,std::string("Button 1"),LGUI::RGBA(50,50,0,255),LGUI::RGBA(255,0,0,0), &window));
    window.setResizable(true);
    while (window.update()) //window main loop
    {
        
    }
                                       


    return 0;
}


