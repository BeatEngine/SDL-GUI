namespace LGUI
{

    ScrollBox::ScrollBox(int x, int y, int width, int hight, RGBA colorFill, RGBA colorBorder, Window* window, UIComponent** componentsNullTerminated = 0)
    {
        onRightClick = NULL;
        onLeftClick = NULL;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        fill = colorFill;
        border = colorBorder;
        if(componentsNullTerminated)
        {
            int i = 0;
            void* nl = 0;
            while(componentsNullTerminated[i])
            {
                components.push_back(componentsNullTerminated[i]);
                if(componentsNullTerminated[i]->hasPosition())
                {
                    relativePositions.push_back(componentsNullTerminated[i]->getPosition());
                }
                else
                {
                    SDL_Rect tmp;
                    tmp.h = 0;
                    tmp.w = 0;
                    tmp.x = box.x;
                    tmp.y = box.y;
                    relativePositions.push_back(tmp);
                }
                i++;
            }
            updateRelativePositions();
        }
    }

    bool ScrollBox::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        window->setColor(fill);
        SDL_RenderFillRect(window->getRenderer(), &box);
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

        for(int i = 0; i < components.size(); i++)
        {
            if(components.at(i)->hasPosition())
            {
                components.at(i)->setDrawBordersRect(box);
                components.at(i)->update(window);
            }
        }

        return false;
    }

    bool ScrollBox::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            window->setColor(fill);
            SDL_RenderFillRect(window->getRenderer(), &box);
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
        for(int i = 0; i < components.size(); i++)
        {
            if(components.at(i)->hasPosition())
            {
                if(components.at(i)->hasPosition())
                {
                    components.at(i)->setDrawBordersRect(box);
                    components.at(i)->update(window, event);
                }
            }
        }
        if(isEnabled())
        {
            if(event.type == SDL_MOUSEWHEEL)
            {
                if(event.wheel.y < 0 && scrollY < 1)
                {
                    setScroll(scrollX, scrollY + (-event.wheel.y*3)/100.0f);
                }
                else if(scrollY > 0)
                {
                    setScroll(scrollX, scrollY - event.wheel.y*3/100.0f);
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        if(onLeftClick != NULL)
                        {
                            void* arr[2];
                            arr[0] = window;
                            arr[1] = this;
                            ((void ((*)(void**)))(onLeftClick))(arr);
                            return true;
                        }
                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        if(onRightClick != NULL)
                        {
                            void* arr[2];
                            arr[0] = window;
                            arr[1] = this;
                            ((void ((*)(void**)))(onRightClick))(arr);
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

}
