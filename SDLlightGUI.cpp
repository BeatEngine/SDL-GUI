#include <stdio.h>

#include "SDLLightGUI.h"

void changeText(void** parameters)
{
    LGUI::Button* button = (LGUI::Button*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];
    std::string txt("Geklickt!");
    window->setColor(LGUI::RGBA(100,0,0,255));
    //button->setText(txt, 12, window->getRenderer());
}

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
    LGUI::Button* button1 = new LGUI::Button(100,50,50,30,std::string("Button 1"),LGUI::RGBA(50,50,0,255),LGUI::RGBA(255,0,0,0), &window);
    window.addComponent(button1);
    window.setResizable(true);

    button1->setOnLeftClick(changeText);
    while (window.update()) //window main loop
    {
        
    }
                                       


    return 0;
}


