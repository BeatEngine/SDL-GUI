namespace LGUI
{

bool InputBox::update(Window* window)
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
        text.update(window);
    }

    bool InputBox::update(Window* window, SDL_Event& event)
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
        text.update(window);

        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if(event.button.x >= box.x && event.button.x <= box.x+box.w)
            {
                if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                {
                    if(onLeftClick != NULL)
                    {
                        selected = !selected;
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
        if(event.type == SDL_KEYDOWN && selected)
        {
            //append(event.text.text, window->getRenderer());
            char ptr[2] = {0};
            ptr[0] = event.key.keysym.sym;
            append(ptr, window->getRenderer());
            /*if(event.button.x >= box.x && event.button.x <= box.x+box.w)
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
            }*/
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
        if(text.length()==0)
        {
            this->text = Text("./Arial.ttf", textSize, text, x+5, y+hight/2-(textSize*4/3)/2, 1, textSize*5/4, window);
        }
        else
        {
            this->text = Text("./Arial.ttf", textSize, text, x+5, y+hight/2-(textSize*4/3)/2, text.size()*textSize/2.150, textSize*5/4, window);
        }
        this->text.setBackground(fill, window->getRenderer());
    }

}

