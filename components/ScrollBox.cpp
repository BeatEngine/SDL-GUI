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
        verticalBar = new LGUI::ScrollBar(x + width - 15, y+1, 14, hight-2, fill, border, window, true);
        horizontalBar = new LGUI::ScrollBar(x + 1, y + hight - 15, width-16, 14, fill, border, window, false);

        verticalBar->setParent(this);
        horizontalBar->setParent(this);

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
        if(fill.a > 0)
        {
            window->setColor(fill);
            SDL_RenderFillRect(window->getRenderer(), &box);
        }
        

        for(int i = 0; i < components.size(); i++)
        {
            if(components.at(i)->hasPosition())
            {
                components.at(i)->setDrawBordersRect(box);
                components.at(i)->update(window);
            }
        }

        if(conditionalShowBars)
        {
            if(horizontalBar->getDisplayQuote()<1)
            {
                horizontalBar->update(window);
            }
            if(verticalBar->getDisplayQuote()<1)
            {
                verticalBar->update(window);
            }
        }
        else
        {
            horizontalBar->update(window);
            verticalBar->update(window);
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

    bool ScrollBox::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            if(fill.a > 0)
            {
                window->setColor(fill);
                SDL_RenderFillRect(window->getRenderer(), &box);
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
        if(!isHidden())
        {
            if(conditionalShowBars)
            {
                if(horizontalBar->getDisplayQuote()<1)
                {
                    horizontalBar->update(window, event);
                }
                if(verticalBar->getDisplayQuote()<1)
                {
                    verticalBar->update(window, event);
                }
            }
            else
            {
                horizontalBar->update(window, event);
                verticalBar->update(window, event);
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
            if(event.type == SDL_MOUSEMOTION)
            {
                lastX = event.motion.x;
                lastY = event.motion.y;
            }
            if(event.type == SDL_MOUSEWHEEL)
            {
                if(lastX >= box.x && lastX <= box.x+box.w)
                {
                    if(lastY >= box.y && lastY <= box.y+box.h)
                    {

                        if(event.wheel.y < 0 && scrollY < 1)
                        {
                            setScroll(scrollX, scrollY + (-event.wheel.y*3)/100.0f);
                        }
                        else if(scrollY > 0)
                        {
                            setScroll(scrollX, scrollY - event.wheel.y*3/100.0f);
                        }
                        if(event.wheel.x > 0 && scrollX < 1)
                        {
                            setScroll(scrollX + event.wheel.x*3/100.0f, scrollY);
                        }
                        else if(scrollX > 0)
                        {
                            setScroll(scrollX + event.wheel.x*3/100.0f, scrollY);
                        }
                    }
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
