
namespace LGUI
{

    CheckBox::CheckBox(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize = 12)
    {
        onRightClick = NULL;
        onLeftClick = NULL;
        fill = colorFill;
        border = colorBorder;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        borderSize = 2;
        this->text = Text("./Arial.ttf", textSize, text, x+width+5, y+hight/2-(textSize*5/4)/2, text.size()*textSize/2.150, textSize*5/4, window);
        this->text.setPositionCenter(x, y + hight/2);
        this->text.setPosition(x+width + 5, this->text.getPosition().y);
        this->text.setBackground(RGBA(255,255,255,0), window->getRenderer());
    }

    bool CheckBox::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        window->setColor(fill);
        SDL_RenderFillRect(window->getRenderer(), &box);
        RGBA col(0, 0, 0, 255);
        window->setColor(col);
        if(selected)
        {
            SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+2, box.x+box.w-2, box.y+box.h-2);
            SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+box.h-2, box.x+box.w-2, box.y+2);

            SDL_RenderDrawLine(window->getRenderer(),box.x+3,box.y+2, box.x+box.w-1, box.y+box.h-2);
            SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+box.h-1, box.x+box.w-2, box.y+3);

            SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+3, box.x+box.w-2, box.y+box.h-1);
            SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+box.h-1, box.x+box.w-2, box.y+3);

        }
        window->setColor(border);
        SDL_Rect tmp = box;
        tmp.h++;
        tmp.w++;
        for(int i = 0; i < borderSize; i++)
        {
            tmp.h-=2;
            tmp.w-=2;
            tmp.x++;
            tmp.y++;
            SDL_RenderDrawRect(window->getRenderer(), &tmp);
        }
        
        text.update(window);
        return false;
    }

    bool CheckBox::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            window->setColor(fill);
            SDL_RenderFillRect(window->getRenderer(), &box);
            RGBA col(0, 0, 0, 255);
            window->setColor(col);
            if(selected)
            {
                SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+2, box.x+box.w-2, box.y+box.h-2);
                SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+box.h-2, box.x+box.w-2, box.y+2);

                SDL_RenderDrawLine(window->getRenderer(),box.x+3,box.y+2, box.x+box.w-1, box.y+box.h-2);
                SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+box.h-1, box.x+box.w-2, box.y+3);

                SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+3, box.x+box.w-2, box.y+box.h-1);
                SDL_RenderDrawLine(window->getRenderer(),box.x+2,box.y+box.h-1, box.x+box.w-2, box.y+3);
            }
            window->setColor(border);
            SDL_Rect tmp = box;
            tmp.h++;
            tmp.w++;
            for(int i = 0; i < borderSize; i++)
            {
                tmp.h-=2;
                tmp.w-=2;
                tmp.x++;
                tmp.y++;
                SDL_RenderDrawRect(window->getRenderer(), &tmp);
            }
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
        }

        return false;
    }

}


