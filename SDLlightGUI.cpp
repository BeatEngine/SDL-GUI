#include <stdio.h>

#include "SDLLightGUI.h"

void changeText(void** parameters)
{
    LGUI::Button* button = (LGUI::Button*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];


    LGUI::InputBox* inp = (LGUI::InputBox*)window->getComponent(1001);
    std::string txt("");
    if(inp)
    {
        txt = inp->getText();
    }

    //window->setTitle(txt);
    
    //button->setTextColor(LGUI::RGBA(0, 0, 0, 255),12, window->getRenderer());
    button->setBorder(LGUI::RGBA(100,100,100,255), 2);
    button->setText(txt, window->getRenderer());
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

void checkBoxOnClick(void** parameters)
{
    LGUI::CheckBox* checkbox = (LGUI::CheckBox*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];

    LGUI::RadioGroup* radioGroup = (LGUI::RadioGroup*)window->getComponent(2001);
    if(checkbox->isSelected())
    {
        if(radioGroup)
        {
            radioGroup->setEnabled(true);
            radioGroup->setHidden(false);
        }
    }
    else
    {
        if(radioGroup)
        {
            radioGroup->setEnabled(false);
            radioGroup->setHidden(true);
        }
    }
}



int main(int args, char** arg)
{
    std::string title = "Light GUI Demo";
    LGUI::Window window(title, 1000, 1000);
    
    LGUI::Button* button1 = new LGUI::Button(100,50,70,30,std::string("Button 1"),LGUI::RGBA(200,200,200,255),LGUI::RGBA(100,100,100,255), &window);

    LGUI::InputBox* input1 = new LGUI::InputBox(300, 50,130,30,std::string(""),LGUI::RGBA(255,255,255,255),LGUI::RGBA(100,100,100,255), &window);
    input1->setId(1001);

    LGUI::RadioBox* radio1 = new LGUI::RadioBox(40, 150, 7, std::string("Radio 1"),LGUI::RGBA(200,200,200,255),LGUI::RGBA(100,100,100,255), &window);
    LGUI::RadioBox* radio2 = new LGUI::RadioBox(40, 170, 7, std::string("Radio 2"),LGUI::RGBA(200,200,200,255),LGUI::RGBA(100,100,100,255), &window);
    LGUI::RadioBox* radio3 = new LGUI::RadioBox(40, 190, 7, std::string("Radio 3"),LGUI::RGBA(200,200,200,255),LGUI::RGBA(100,100,100,255), &window);
    LGUI::RadioBox* list[] = {radio1, radio2, radio3, NULL};
    LGUI::RadioGroup* radioGroup = new LGUI::RadioGroup(list);
    radioGroup->setId(2001);
    radioGroup->setEnabled(false);
    radioGroup->setHidden(true);

    LGUI::CheckBox* check1 = new LGUI::CheckBox(40, 120, 14, 14, std::string("Enable and show radio control"), LGUI::RGBA(200,200,200,255),LGUI::RGBA(100,100,100,255), &window);

    window.addComponent(button1);
    window.addComponent(input1);
    window.addComponent(check1);
    window.addComponent(radioGroup);
    window.setResizable(true);

    button1->setOnLeftClick(changeText);
    input1->setOnLeftClick(textboxOnClick);
    radio1->setBorder(LGUI::RGBA(70,70,70,255), 2);
    radio2->setBorder(LGUI::RGBA(70,70,70,255), 2);
    radio3->setBorder(LGUI::RGBA(70,70,70,255), 2);
    check1->setOnLeftClick(checkBoxOnClick);
    while (window.update()) //window main loop
    {
        window.updateScreen();
    }

    return 0;
}


