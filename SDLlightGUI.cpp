#include <stdio.h>

#include "SDLLightGUI.h"

void changeText(void** parameters)
{
    LGUI::Button* button = (LGUI::Button*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];
    std::string txt("Geklickt!");
    //window->setTitle(txt);
    
    //button->setText(txt, 12, window->getRenderer());
    printf("Set text!\n");
}

int main(int args, char** arg)
{
    std::string title = "Light GUI Demo";
    LGUI::Window window(title, 1000, 1000);
    
    LGUI::Button* button1 = new LGUI::Button(100,50,50,30,std::string("Button 1"),LGUI::RGBA(50,50,0,255),LGUI::RGBA(255,0,0,0), &window);
    window.addComponent(button1);
    window.setResizable(true);

    button1->setOnLeftClick(changeText);
    while (window.update()) //window main loop
    {
        window.updateScreen();
    }
                                       


    return 0;
}


