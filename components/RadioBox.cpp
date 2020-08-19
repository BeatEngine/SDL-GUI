
namespace LGUI
{

    RadioBox::RadioBox(int x, int y, int radius, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize = 12)
    {
        onRightClick = NULL;
        onLeftClick = NULL;
        fill = colorFill;
        border = colorBorder;
        this->radius = radius;
        this->x = x;
        this->y = y;
        this->text = Text("./Arial.ttf", textSize, text, x+radius+5, y-(textSize*5/4)/2, text.size()*textSize/2.150, textSize*5/4, window);
        this->text.setBackground(RGBA(255,255,255,0), window->getRenderer());
    }

    bool RadioBox::update(Window* window)
    {
        window->setColor(fill);
        renderFillCircle(window->getRenderer(), x, y, radius);
        window->setColor(border);
        if(selected)
        {
            renderFillCircle(window->getRenderer(), x, y, radius/2);
            renderDrawCircle(window->getRenderer(), x, y, radius/2, radius/2);
        }
        renderDrawCircle(window->getRenderer(), x, y, radius, borderSize);
        text.update(window);
        return false;
    }

    bool RadioBox::update(Window* window, SDL_Event& event)
    {
        window->setColor(fill);
        renderFillCircle(window->getRenderer(), x, y, radius);
        window->setColor(border);
        if(selected)
        {
            renderFillCircle(window->getRenderer(), x, y, radius/2);
            renderDrawCircle(window->getRenderer(), x, y, radius/2, radius/2);
        }
        renderDrawCircle(window->getRenderer(), x, y, radius, borderSize);
        text.update(window);

        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int dx = event.button.x-x;
            int dy = event.button.y-y;
            if(sqrt(dx*dx+dy*dy) <= radius)
            {
                selected = !selected;
                if(onLeftClick != NULL)
                {
                    void* arr[2];
                    arr[0] = window;
                    arr[1] = this;
                    ((void ((*)(void**)))(onLeftClick))(arr);
                }
                return true;
            }
        }
        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
        {
            int dx = event.button.x-x;
            int dy = event.button.y-y;
            if(sqrt(dx*dx+dy*dy) <= radius)
            {
                if(onRightClick != NULL)
                {
                    void* arr[2];
                    arr[0] = window;
                    arr[1] = this;
                    ((void ((*)(void**)))(onRightClick))(arr);   
                }
            }
        }

        return false;
    }

}


