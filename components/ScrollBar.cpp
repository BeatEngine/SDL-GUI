namespace LGUI
{

    static int positive(int x)
    {
        if(x < 0)
        {
            return -x;
        }
        return x;
    }

    ScrollBar::ScrollBar(int x, int y, int width, int hight, RGBA colorFill, RGBA colorBorder, Window* window, bool vertical)
    {
        onRightClick = NULL;
        onLeftClick = NULL;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        fill = colorFill;
        border = colorBorder;
        this->vertical = vertical;
        button = new Button(box.x + 1, box.y + 1, box.w - 2, box.h - 2, std::string(""), RGBA(200, 200, 200, 255), RGBA(100, 100, 100, 255), window, 6);
    }

    bool ScrollBar::update(Window* window)
    {
        if(button->getParentWhenSet() == NULL)
        {
            button->setParent(this);
        }
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
        button->update(window);
        return false;
    }

    void ScrollBar::_scrollParentOnClick(void** params)
    {
        LGUI::Button* button = (LGUI::Button*)params[1];
        LGUI::Window* window = (LGUI::Window*)params[0];

        LGUI::ScrollBar* scrollBar = (LGUI::ScrollBar*)button->getParentWhenSet();

        SDL_Event* eventptr = (SDL_Event*)params[2];

        scrollBar->setLastCursor(eventptr->button.x, eventptr->button.y);
    }

    void ScrollBar::scrollOnClick(SDL_Event& event, LGUI::ScrollBox* scroll)
    {
        int motionX = lastX - event.motion.x;
        int motionY = lastY - event.motion.y;

        if(vertical)
        {
            motionX = 0;
            if(motionY != 0)
            {
                //motionY /= positive(motionY);
            }
        }
        else
        {
            motionY = 0;
            //motionX = -motionX;
            if(motionX != 0)
            {
                //motionX /= positive(motionX);
            }
        }
    
        if(motionY < 0 && scroll->getScrollY() < 1)
        {
            scroll->setScroll(scroll->getScrollX(), scroll->getScrollY() + (-motionY*3)/100.0f);
        }
        else if(scroll->getScrollY() > 0)
        {
            scroll->setScroll(scroll->getScrollX(), scroll->getScrollY() - motionY*3/100.0f);
        }
        if(motionX > 0 && scroll->getScrollX() < 1)
        {
            scroll->setScroll(scroll->getScrollX() + motionX*3/100.0f, scroll->getScrollY());
        }
        else if(scroll->getScrollX() > 0)
        {
            scroll->setScroll(scroll->getScrollX() + motionX*3/100.0f, scroll->getScrollY());
        }

    }

    
    bool ScrollBar::update(Window* window, SDL_Event& event)
    {
        if(button->getParentWhenSet() == NULL)
        {
            button->setParent(this);
            //button->setOnLeftClick(LGUI::ScrollBar::_scrollParentOnClick);
        }
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
        button->update(window, event);
        if(isEnabled())
        {
            if(event.type == SDL_MOUSEMOTION)
            {
                if(lastX != -1 && lastY != -1)
                {
                    scrollOnClick(event, (LGUI::ScrollBox*)optionalParent);
                    lastY = event.motion.y;
                    lastX = event.motion.x;
                return true;
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        scrollParentOnClick(event);
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
            if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                lastX = -1;
                lastY = -1;
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
