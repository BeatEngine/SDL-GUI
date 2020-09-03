namespace LGUI
{

    List::List(int x, int y, int width, int hight, RGBA colorFill, RGBA colorBorder, Window* window, UIComponent** elementsListNullTerminated = 0)
    {
        onRightClick = NULL;
        onLeftClick = NULL;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        fill = colorFill;
        border = colorBorder;

        if(elementsListNullTerminated)
        {
            int i = 0;
            while (elementsListNullTerminated[i])
            {
                elements.push_back(elementsListNullTerminated[i]);
                i++;
            }
            setElementsPositions();
        }
        
    }

    bool List::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        window->setColor(fill);
        if(rectIsInBorders(box))
        {
            SDL_RenderFillRect(window->getRenderer(), &box);
        }
        else
        {
            SDL_Rect tmprect = cropToDrawBorders(box);
            SDL_RenderFillRect(window->getRenderer(),&tmprect);
        }
        window->setColor(border);
        SDL_Rect tmp = box;
        if(rectIsInBorders(box))
        {
            for(int i = 0; i < borderSize; i++)
            {
                SDL_RenderDrawRect(window->getRenderer(), &tmp);
                tmp.h-=2;
                tmp.w-=2;
                tmp.x++;
                tmp.y++;
            }
        }
        for(int i = 0; i < elements.size(); i++)
        {
            elements.at(i)->setDrawBordersRect(getDrawBorderRect());
            elements.at(i)->update(window);
        }
        return false;
    }

    bool List::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            window->setColor(fill);
            if(rectIsInBorders(box))
            {
                SDL_RenderFillRect(window->getRenderer(), &box);
            }
            else
            {
                SDL_Rect tmprect = cropToDrawBorders(box);
                SDL_RenderFillRect(window->getRenderer(),&tmprect);
            }
            window->setColor(border);
            SDL_Rect tmp = box;
            if(rectIsInBorders(box))
            {
                for(int i = 0; i < borderSize; i++)
                {
                    SDL_RenderDrawRect(window->getRenderer(), &tmp);
                    tmp.h-=2;
                    tmp.w-=2;
                    tmp.x++;
                    tmp.y++;
                }
            }
        }
        for(int i = 0; i < elements.size(); i++)
        {
            elements.at(i)->setDrawBordersRect(getDrawBorderRect());
            elements.at(i)->update(window, event);
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
