namespace LGUI
{

    MenuEntriy::~MenuEntriy()
    {
        if(subMenu)
        {
            delete subMenu;
        }
    }

    MenuEntriy::MenuEntriy(int x, int y, int width, int hight, std::string text, Window* window, int textSize, MenuList* setSubMenu)
    {
        subMenu = setSubMenu;
        onRightClick = NULL;
        onLeftClick = NULL;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        this->text = Text("./Arial.ttf", textSize, text, x+width/2-text.size()*textSize/4.30, y+hight/2-(textSize*4/3)/2, text.size()*textSize/2.150, textSize*5/4, window);
        this->text.setPositionCenter(x + box.w/2, y + box.h/2);
        this->text.setPosition(x + 15, this->text.getPosition().y);
        this->text.setBackground(RGBA(255,255,255,0), window->getRenderer());
    }

    bool MenuEntriy::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        text.update(window);
        return false;
    }

    bool MenuEntriy::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            text.update(window);
        }
        if(isEnabled())
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        if(onLeftClick != NULL)
                        {
                            void* arr[3];
                            arr[0] = window;
                            arr[1] = this;
                            arr[2] = &event;
                            ((void ((*)(void**)))(onLeftClick))(arr);
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    MenuList::MenuList(int x, int y, int width, int hight, RGBA colorFill,RGBA colorSelect, RGBA colorBorder, Window* window, int textSize = 12)
    {
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        fill = colorFill;
        border = colorBorder;
        selectColor = colorSelect;
        selectBox.h = 0;
        selectBox.x = box.x;
        selectBox.w = box.w;
        selectBox.y = box.y;
    }

    bool MenuList::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        
        window->setColor(fill);
        SDL_RenderFillRect(window->getRenderer(), &box);
        if(mouseInBox)
        {
            window->setColor(selectColor);
            SDL_RenderFillRect(window->getRenderer(), &selectBox);
        }
        for(int i = 0; i  < entries.size(); i++)
        {
            entries.at(i)->update(window);
        }
        window->setColor(border);
        SDL_Rect tmp = box;
        for(int i = 0; i < borderSize; i++)
        {
            SDL_RenderDrawRect(window->getRenderer(), &tmp);
            tmp.h-=2;
            tmp.w-=2;
            tmp.x++;
            tmp.y++;
        }
        return false;
    }

    bool MenuList::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            window->setColor(fill);
            SDL_RenderFillRect(window->getRenderer(), &box);
            if(mouseInBox)
            {
                window->setColor(selectColor);
                SDL_RenderFillRect(window->getRenderer(), &selectBox);
            }
            for(int i = 0; i  < entries.size(); i++)
            {
                entries.at(i)->update(window, event);
            }
            window->setColor(border);
            SDL_Rect tmp = box;
            for(int i = 0; i < borderSize; i++)
            {
                SDL_RenderDrawRect(window->getRenderer(), &tmp);
                tmp.h-=2;
                tmp.w-=2;
                tmp.x++;
                tmp.y++;
            }
        }
        if(isEnabled())
        {
            if(overlappedComponents.size() == 0)
            {
                overlappedComponents = window->getComponents(box);
                for(int i = 0; i < overlappedComponents.size(); i++)
                {
                    if(!overlappedComponents.at(i)->isEnabled())
                    {
                        overlappedComponents.erase(overlappedComponents.begin()+i);
                        i--;
                    }
                    else
                    {
                        overlappedComponents.at(i)->setEnabled(false);
                    }
                }
                setProperties(isHidden(), true);
                UIComponent* parent = getParentWhenSet();
                if (parent)
                {
                    parent->setProperties(parent->isHidden(), true);
                }
                
            }
            if(event.type == SDL_MOUSEMOTION)
            {
                mouseInBox = false;
                if(event.motion.x >= box.x && event.motion.x <= box.x+box.w)
                {
                    if(event.motion.y >= box.y && event.motion.y < box.y+box.h && entries.size() > 0)
                    {
                        mouseInBox = true;
                        selectBox.h = entries.at(0)->getRect().h;
                        selectBox.x = box.x;
                        int indx = (int)((event.motion.y-box.y) / (float)box.h * entries.size());
                        selectBox.y = box.y+indx*entries.at(0)->getRect().h;
                        
                        
                    }
                }
            }
        }

        return false;
    }

}
