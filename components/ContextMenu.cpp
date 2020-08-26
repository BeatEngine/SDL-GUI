namespace LGUI
{

    ContextMenu::ContextMenu(int x, int y, int width, int hight, MenuList* menu, Window* window)
    {
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        this->menu = menu;
        this->menu->setParent(this);
        this->setHidden(true);
        menu->setEnabled(false);
    }

    bool ContextMenu::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        menu->update(window);
        return false;
    }

    bool ContextMenu::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            menu->update(window, event);
        }
        if(isEnabled())
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        this->setHidden(true);
                        menu->setEnabled(false);
                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        this->menu->setPosition(event.button.x, event.button.y);
                        this->setHidden(false);
                        menu->setEnabled(true);
                    }
                }
            }
        }

        return false;
    }

}
