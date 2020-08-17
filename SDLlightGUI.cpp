#include <stdio.h>

#include "SDLLightGUI.h"

void changeText(void** parameters)
{
    LGUI::Button* button = (LGUI::Button*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];
    std::string txt("Geklickt!");
    //window->setTitle(txt);
    
    //button->setTextColor(LGUI::RGBA(0, 0, 0, 255),12, window->getRenderer());
    button->setBorder(LGUI::RGBA(100,100,100,255), 2);
    button->setText(txt, window->getRenderer());
    printf("Set text!\n");
}

void textboxOnClick(void** parameters)
{
    LGUI::InputBox* inputbox = (LGUI::InputBox*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];

    if(inputbox->isSelected())
    {
        inputbox->setBorder(LGUI::RGBA(100,100,100,255) , 2);
    }
    else
    {
        inputbox->setBorder(LGUI::RGBA(100,100,100,255));
        std::string txt = inputbox->getText();
    }
    
}



int main(int args, char** arg)
{
    std::string title = "Light GUI Demo";
    LGUI::Window window(title, 1000, 1000);
    
    LGUI::Button* button1 = new LGUI::Button(100,50,70,30,std::string("Button 1"),LGUI::RGBA(200,200,200,255),LGUI::RGBA(100,100,100,255), &window);

    LGUI::InputBox* input1 = new LGUI::InputBox(300, 50,130,30,std::string(""),LGUI::RGBA(255,255,255,255),LGUI::RGBA(100,100,100,255), &window);

    LGUI::RadioBox* radio1 = new LGUI::RadioBox(40, 65, 7, std::string("Radio 1"),LGUI::RGBA(200,200,200,255),LGUI::RGBA(100,100,100,255), &window);

    window.addComponent(button1);
    window.addComponent(input1);
    window.addComponent(radio1);
    window.setResizable(true);

    button1->setOnLeftClick(changeText);
    input1->setOnLeftClick(textboxOnClick);
    radio1->setBorder(LGUI::RGBA(0,0,0,255), 2);
    while (window.update()) //window main loop
    {
        window.updateScreen();
    }

    return 0;
}


