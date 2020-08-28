
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

void contextOnExit(void** parametes)
{
    exit(0);
}

void imageOnMouseMove(void** parameters)
{
    LGUI::Sprite* sprite = (LGUI::Sprite*)parameters[1];
    LGUI::Window* window = (LGUI::Window*)parameters[0];
    SDL_Event* motionEvent = (SDL_Event*)parameters[2];
    if(sprite->isLeftButtonDown() && sprite->getLastMouseX() >= 0 && sprite->getLastMouseY() >= 0)
    {
        int mx = motionEvent->motion.x - sprite->getLastMouseX();
        int my = motionEvent->motion.y - sprite->getLastMouseY();

        SDL_Rect pos = sprite->getPosition();
        pos.x += mx;
        pos.y += my;
        sprite->setPosition(pos.x, pos.y, window);
        //sprite->setLastCursorPosition(pos.x, pos.y);
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


    LGUI::Button* button2 = new LGUI::Button(50, 440, 100, 20, std::string("Button in tab 1"), LGUI::RGBA(200,255,200,255), LGUI::RGBA(0,0,100,255), &window);
    LGUI::Button* button3 = new LGUI::Button(50, 480, 100, 20, std::string("2. Button in tab 1"), LGUI::RGBA(200,255,200,255), LGUI::RGBA(0,0,100,255), &window);

    LGUI::Button* button4 = new LGUI::Button(50, 440, 100, 20, std::string("Button in tab 2"), LGUI::RGBA(200,255,200,255), LGUI::RGBA(0,0,100,255), &window);
    LGUI::Button* button5 = new LGUI::Button(200, 440, 100, 20, std::string("2. Button in tab 2"), LGUI::RGBA(200,255,200,255), LGUI::RGBA(0,0,100,255), &window);


    LGUI::Text* element1 = new LGUI::Text("This", 14, &window);
    LGUI::Text* element2 = new LGUI::Text("is", 14, &window);
    LGUI::Text* element3 = new LGUI::Text("a", 14, &window);
    LGUI::Text* element4 = new LGUI::Text("list", 14, &window);
    LGUI::Text* element5 = new LGUI::Text("to", 14, &window);
    LGUI::Text* element6 = new LGUI::Text("demonstrate", 14, &window);
    LGUI::Text* element7 = new LGUI::Text("the", 14, &window);
    LGUI::Text* element8 = new LGUI::Text("GUI-elements", 14, &window);

    LGUI::UIComponent* elements1[] = {element1, element2, element3, element4, NULL};
    LGUI::List* list1 = new LGUI::List(0, 0, 300, 560, LGUI::RGBA(230, 230, 230, 255), LGUI::RGBA(50, 50, 50, 255), &window, elements1);

    

    list1->push(element5);
    list1->push(element6);
    list1->push(element7);
    list1->push(element8);

    LGUI::UIComponent* elements2[] = {list1, NULL};
    LGUI::ScrollBox* scroll1 = new LGUI::ScrollBox(50, 440, 200, 400, LGUI::RGBA(255, 255, 255, 0), LGUI::RGBA(0, 0, 0, 255), &window, elements2);


    LGUI::ProgressBar* progressScroll = new LGUI::ProgressBar(400, 400, 300,20,"scrollY: ", LGUI::RGBA(100, 255, 100, 255), LGUI::RGBA(240, 240, 240, 255), LGUI::RGBA(50, 50, 50, 0), &window, true, 14);

    progressScroll->setBoxCornerRadius(0.95);
    progressScroll->setBorder(LGUI::RGBA(50, 50, 50, 255),  1);

    LGUI::UIComponent* components1[] = {button2, button3, NULL};
    LGUI::UIComponent* components2[] = {button4, button5, NULL};
    LGUI::UIComponent* components3[] = {scroll1, progressScroll, NULL};

    LGUI::ContainerTab* tab1 = new LGUI::ContainerTab(std::string("Tab 1"), components1);
    LGUI::ContainerTab* tab2 = new LGUI::ContainerTab(std::string("Tab 2"), components2);
    LGUI::ContainerTab* tab3 = new LGUI::ContainerTab(std::string("Tab 3"), components3);
    LGUI::ContainerTab* tabs[] = {tab1, tab2, tab3, NULL};
    LGUI::TabbedContainer* container = new LGUI::TabbedContainer(&window,tabs);

    container->setPosition(0, 400, &window);

    LGUI::UIComponent* contlist[] = {container, NULL};

    LGUI::ScrollBox* content = new LGUI::ScrollBox(0, 0, 1000, 1000, LGUI::RGBA(255,255,255,0),LGUI::RGBA(0, 0, 0, 255), &window, contlist);

    LGUI::MenuList* menuContext = new LGUI::MenuList(0, 0, 70, 200,LGUI::RGBA(240, 240, 240, 255), LGUI::RGBA(220, 220, 220, 255), LGUI::RGBA(0, 0, 0, 255), &window);

    menuContext->addEntrie("Exit", &window, contextOnExit);
    menuContext->addEntrie("Brexit", &window, contextOnExit);
    menuContext->addEntrie("Lexit", &window, contextOnExit);
    menuContext->addEntrie("Nexit", &window, contextOnExit);

    LGUI::ContextMenu* contextMenu = new LGUI::ContextMenu(0, 0, 9999, 9999, menuContext, &window);
    contextMenu->setLayer(2);

    LGUI::Sprite* image1 = new LGUI::Sprite(450,100,500,500, LGUI::RGBA(0, 0, 0, 255), &window, "Components.png");
    image1->setBorder(LGUI::RGBA(0, 0, 0, 255), 1);
    image1->setFitRules(true);
    image1->setLayer(0);
    image1->setOnMouseMove(imageOnMouseMove);

    window.addComponent(container);

    window.addComponent(contextMenu);

    window.addComponent(image1);
    while (window.update()) //window main loop
    {
        progressScroll->setProgress(scroll1->getScrollY(), window.getRenderer());
        window.updateScreen();
    }

    return 0;
}


