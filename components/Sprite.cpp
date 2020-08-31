namespace LGUI
{

    Sprite::Sprite(int x, int y, int width, int hight, RGBA colorBorder, Window* window, std::string loadFromFilePath = "")
    {
        setParent(0);
        onRightClick = NULL;
        onLeftClick = NULL;
        onMouseEnter = NULL;
        onMouseLeft = NULL;
        onMouseMove = NULL;
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

    void Sprite::setPosition(int x, int y,bool center = false, Window* window = 0)
    {
        if(x <= 0)
        {
            x = 1;
        }
        if(y <= 0)
        {
            y = 1;
        }
        if(window)
        {
            SDL_Rect tmp = getPositionScaled(window);
            if(fitParent && getParentWhenSet() != NULL)
            {
                /*if(y + tmp.h > getParentWhenSet()->getPosition().h)
                {
                    y = getParentWhenSet()->getPosition().h-tmp.h;
                }*/
            }
            else if(window)
            {
                if(y + tmp.h >= window->getRect().h)
                {
                    y = window->getRect().h - tmp.h - 1;
                }
                if(x + box.w >= window->getRect().w)
                {
                    x = window->getRect().w - box.w - 1;
                }
            }
        }
        if(!center)
        {
            box.x = x+box.w/2;
            box.y = y+box.h/2;
        }
        else
        {
            box.x = x;
            box.y = y;
        }
    }



    SDL_Rect Sprite::getPositionScaled(Window* window)
    {
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
                tmp.w = window->getRect().w - tmp.x-1;
                tmp.h = window->getRect().h - tmp.y-1;
            }
            else
            {
                tmp.w = tparent->getDrawBorderRect().w-1;
                tmp.h = tparent->getDrawBorderRect().h-1;
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
        return tmp;
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
                tmp.w = window->getRect().w - tmp.x-1;
                tmp.h = window->getRect().h - tmp.y-1;
            }
            else
            {
                tmp.w = tparent->getDrawBorderRect().w-1;
                tmp.h = tparent->getDrawBorderRect().h-1;
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
        //tmp = cropToDrawBorders(box);
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
            bool ret = false;
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
                    tmp.w = window->getRect().w - tmp.x-1;
                    tmp.h = window->getRect().h - tmp.y-1;
                }
                else
                {
                    tmp.w = tparent->getDrawBorderRect().w-1;
                    tmp.h = tparent->getDrawBorderRect().h-1;
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
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= tmp.x && event.button.x <= tmp.x+tmp.w)
                {
                    if(event.button.y >= tmp.y && event.button.y <= tmp.y+tmp.h)
                    {
                        
                        mouseButtonDown = true;
                        if(onLeftClick != NULL)
                        {
                            void* arr[3];
                            arr[0] = window;
                            arr[1] = this;
                            arr[2] = &event;
                            ((void ((*)(void**)))(onLeftClick))(arr);
                            ret =  true;
                        }
                        lastMouseX = event.button.x;
                        lastMouseY = event.button.y;
                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
            {
                if(event.button.x >= tmp.x && event.button.x <= tmp.x+tmp.w)
                {
                    if(event.button.y >= tmp.y && event.button.y <= tmp.y+tmp.h)
                    {
                        if(onRightClick != NULL)
                        {
                            void* arr[3];
                            arr[0] = window;
                            arr[1] = this;
                            arr[2] = &event;
                            ((void ((*)(void**)))(onRightClick))(arr);
                            ret = true;
                        }
                    }
                }
            }
            if(event.type == SDL_MOUSEMOTION)
            {
                if(event.motion.x >= tmp.x && event.motion.x <= tmp.x+tmp.w)
                {
                    if(event.motion.y >= tmp.y && event.motion.y <= tmp.y+tmp.h)
                    {
                        if(!mouseInside)
                        {
                            mouseInside = true;
                            if(onMouseEnter != NULL)
                            {
                                void* arr[3];
                                arr[0] = window;
                                arr[1] = this;
                                arr[2] = &event;
                                ((void ((*)(void**)))(onMouseEnter))(arr);
                                ret = true;
                            }
                        }
                        if(onMouseMove != NULL)
                        {
                            void* arr[3];
                            arr[0] = window;
                            arr[1] = this;
                            arr[2] = &event;
                            ((void ((*)(void**)))(onMouseMove))(arr);
                            ret = true;
                        }
                        lastMouseX = event.motion.x;
                        lastMouseY = event.motion.y;
                        
                    }
                    else if(mouseInside)
                    {
                        mouseInside = false;
                        if(onMouseLeft != NULL)
                        {
                            void* arr[3];
                            arr[0] = window;
                            arr[1] = this;
                            arr[2] = &event;
                            ((void ((*)(void**)))(onMouseLeft))(arr);
                            ret = true;
                        }
                    }
                }
                else if(mouseInside)
                {
                    mouseInside = false;
                    if(onMouseLeft != NULL)
                    {
                        void* arr[3];
                        arr[0] = window;
                        arr[1] = this;
                        arr[2] = &event;
                        ((void ((*)(void**)))(onMouseLeft))(arr);
                        ret = true;
                    }
                }
            }
            if(mouseButtonDown && event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                mouseButtonDown = false;
                lastMouseX = -1;
                lastMouseY = -1;
            }
            return ret;
        }

        return false;
    }

}
