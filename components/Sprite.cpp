namespace LGUI
{

    Sprite::Sprite(int x, int y, int width, int hight, RGBA colorBorder, Window* window, std::string loadFromFilePath = "")
    {
        setParent(0);
        onRightClick = NULL;
        onLeftClick = NULL;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        border = colorBorder;
        if(loadFromFilePath.size() > 0)
        {
            load(loadFromFilePath, window->getRenderer());
        }
    }

    bool Sprite::update(Window* window)
    {
        if(isHidden() || !loaded)
        {
            return false;
        }
        //SDL_RenderSetScale(window->getRenderer(), box.w/(float)(image->w), box.h/(float)(image->h));
        SDL_Rect tmp = box;
        if(!fitBox)
        {
            tmp.w = image->w;
            tmp.h = image->h;
        }
        if(fitParent)
        {
            UIComponent* tparent = getParentWhenSet();
            if(tparent == 0)
            {
                tmp.w = window->getRect().w - tmp.x;
                tmp.h = window->getRect().h - tmp.y;
            }
            else
            {
                tmp.w = tparent->getDrawBorderRect().w;
                tmp.h = tparent->getDrawBorderRect().h;
            }
        }
        if(fixedAspectRatio)
        {
            if(image->w > image->h)
            {
                tmp.h =(int)(tmp.w * image->h / (float)image->w);
            }
            else
            {
                tmp.w = (int)(tmp.h * image->w / (float)image->h);
            }
        }
        if(rectIsInBorders(tmp))
        {
            if(SDL_RenderCopy(window->getRenderer(), texture, NULL, &tmp) != 0)
            {
                printf("Text: SDL-Error: %s\n", SDL_GetError());
            }
        }
        else
        {
            SDL_Rect cropped = cropToDrawBorders(tmp);
            if(SDL_RenderCopy(window->getRenderer(), texture, &cropped, &tmp) != 0)
            {
                printf("Text: SDL-Error: %s\n", SDL_GetError());
            }
        }
        //SDL_RenderSetScale(window->getRenderer(), 1.00f, 1.00f);
        window->setColor(border);
        tmp = cropToDrawBorders(box);
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

    bool Sprite::update(Window* window, SDL_Event& event)
    {
        update(window);
        if(isEnabled())
        {
            /*if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
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
            */
        }

        return false;
    }

}
