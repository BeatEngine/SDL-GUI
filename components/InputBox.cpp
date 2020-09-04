namespace LGUI
{

    bool InputBox::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        if(selected)
        {
            RGBA tmpsc = fill;
            tmpsc.b /= 1.5;
            window->setColor(tmpsc);
        }
        else
        {
            window->setColor(fill);
        }
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
        text.update(window);
        return false;
    }

    bool InputBox::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            window->setColor(fill);
            if(selected)
            {
                RGBA tmpsc = fill;
                tmpsc.b /= 1.5;
                window->setColor(tmpsc);
            }
            else
            {
                window->setColor(fill);
            }
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
            text.update(window);
        }
        if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_CAPSLOCK)
        {
            lockShift = !lockShift; 
        }
        if(isEnabled())
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        selected = !selected;
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
            if(event.type == SDL_KEYUP && (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT || event.key.keysym.scancode == SDL_SCANCODE_RSHIFT))
            {
                shift = false;
            }

            if(selected && event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
            {
                pop(window->getRenderer());
            }
            else if(selected && event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_DELETE)
            {
                clear(window->getRenderer());
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN && selected)
            {
                char ptr[2] = {0};
                ptr[0] = '\n';
                if(lineBreak)
                {
                    append(ptr, window->getRenderer());
                }
                else
                {
                    selected = false;
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
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_TAB && selected)
            {
                char ptr[2] = {0};
                ptr[0] = '\t';
                append(ptr, window->getRenderer());
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && selected)
            {
                selected = false;
                if(onLeftClick != NULL)
                {
                    void* arr[2];
                    arr[0] = window;
                    arr[1] = this;
                    ((void ((*)(void**)))(onLeftClick))(arr);
                    return true;
                }
            }
            else if(event.type == SDL_KEYDOWN && selected)
            {
                //append(event.text.text, window->getRenderer());
                char ptr[2] = {0};
                ptr[0] = event.key.keysym.sym;
                if(event.key.keysym.scancode == SDL_SCANCODE_LSHIFT || event.key.keysym.scancode == SDL_SCANCODE_RSHIFT)
                {
                    shift = true;
                }
                else if(event.key.keysym.scancode != SDL_SCANCODE_CAPSLOCK)
                {
                    if(lockShift ^ shift)
                    {
                        ptr[0] -= 32;
                    }
                    append(ptr, window->getRenderer());
                }
                
            }
        }
        
        return false;
    }

    InputBox::InputBox(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize = 12)
    {
        onRightClick = NULL;
        onLeftClick = NULL;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        fill = colorFill;
        border = colorBorder;
        
        this->setTextColor(RGBA(~fill.r, ~fill.g, ~fill.b, 255), textSize, window->getRenderer());
        this->text.setPosition(x+5, y+hight/2-(textSize*4/3)/2);
        this->setText(text, window->getRenderer(), 12);
        this->update(window);
        //window->update();
        this->text.setBackground(fill, window->getRenderer());
        //this->update(window);
        //window->update();
        //this->setText(text, window->getRenderer(), 12);
        
    }

}

