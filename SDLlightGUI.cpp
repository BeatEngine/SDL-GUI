#include <stdio.h>

#include "SDLLightGUI.h"

void changeText(void** parameters)
{
    LGUI::Button* button = (LGUI::Button*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];
    std::string txt("Geklickt!");
    //window->setTitle(txt);
    
    //button->setTextColor(LGUI::RGBA(0, 0, 0, 255),12, window->getRenderer());
    button->setText(txt, window->getRenderer());
    printf("Set text!\n");
}

int main(int args, char** arg)
{
    std::string title = "Light GUI Demo";
    LGUI::Window window(title, 1000, 1000);
    
    LGUI::Button* button1 = new LGUI::Button(100,50,70,30,std::string("Button 1"),LGUI::RGBA(200,200,200,255),LGUI::RGBA(200,200,200,255), &window);
    window.addComponent(button1);
    window.setResizable(true);

    button1->setOnLeftClick(changeText);
    while (window.update()) //window main loop
    {
        window.updateScreen();
    }
                                       


    return 0;
}


