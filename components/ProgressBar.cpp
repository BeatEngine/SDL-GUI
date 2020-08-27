namespace LGUI
{

    ProgressBar::ProgressBar(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBackground, RGBA colorBorder, Window* window, bool showNumericalProgress = false, int textSize = 12)
    {
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        lableText = text;
        fill = colorFill;
        border = colorBorder;
        background = colorBackground;
        std::string resTxt = text + " 0%";
        this->text = Text("./Arial.ttf", textSize, resTxt, x+width/2-text.size()*textSize/4.30, y+hight/2-(textSize*4/3)/2, text.size()*textSize/2.150, textSize*5/4, window);
        this->text.setPositionCenter(x + box.w/2, y + box.h/2);
        this->text.setBackground(fill, window->getRenderer());
    }

    bool ProgressBar::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        window->setColor(background);
        renderFillBoxRounded2(window->getRenderer(), box.x, box.y, box.w, box.h, cornerRadius, 9999, 9999);
        SDL_Rect tmp = box;
        window->setColor(fill);
        renderFillBoxRounded2(window->getRenderer(), tmp.x, tmp.y, tmp.w, tmp.h, cornerRadius, tmp.w * progress, 9999);
        window->setColor(border);
        renderDrawBoxRounded2(window->getRenderer(), box.x, box.y, box.w, box.h, cornerRadius, borderSize, 9999, 9999);
        if(showText)
        {
            text.update(window);
        }
        return false;
    }

    bool ProgressBar::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            window->setColor(background);
            renderFillBoxRounded2(window->getRenderer(), box.x, box.y, box.w, box.h, cornerRadius);
            SDL_Rect tmp = box;
            window->setColor(fill);
            renderFillBoxRounded2(window->getRenderer(), tmp.x, tmp.y, tmp.w, tmp.h, cornerRadius, tmp.w * progress);
            window->setColor(border);
            renderDrawBoxRounded2(window->getRenderer(), box.x, box.y, box.w, box.h, cornerRadius, borderSize);
            if(showText)
            {
                text.update(window);
            }
        }
        if(isEnabled())
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        int tmpi = 0;
                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {
                        int tmpi = 0;
                    }
                }
            }
        }

        return false;
    }

}
