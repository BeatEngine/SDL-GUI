namespace LGUI
{
    Table::Table(int x, int y, RGBA colorFill, RGBA colorBorder, Window* window, int textSize = 12)
    {
        defaultTextSize = textSize;
        box.x = x;
        box.y = y;
        box.w = 0;
        box.h = 0;
        fill = colorFill;
        border = colorBorder;
        tableWindow = window;
        update(window);
    }

    void Table::setText(int row, int column, std::string text)
    {
        if(row*columns+column < cells.size())
        {
            cells[row*columns+column].setText(text, tableWindow->getRenderer(), defaultTextSize);     
        }
    }

    bool Table::update(Window* window)
    {
        if(isHidden())
        {
            return false;
        }
        window->setColor(fill);
        SDL_RenderFillRect(window->getRenderer(), &box);

        SDL_Point p[2];
        int h = 0;
        int w = 0;
        
        for(int i = 0; i < cells.size(); i++)
        {
            cells[i].update(window);
        }
        for(int i = 1; i < columns; i++)
        {
            h = box.h;
            w += (cells[i].getRect().x-box.x);
            w -= (cells[i-1].getRect().x-box.x);
            p[0].x = box.x+w;
            p[0].y = box.y;
            p[1].x = box.x+w;
            p[1].y = box.y+h;
            window->setColor(border);
            SDL_RenderDrawLines(window->getRenderer(),p ,2);
        }
        h = 0;
        w = box.w-1;
        for(int i = 1; i <= rows; i++)
        {
            h += (cells[i*columns].getRect().y-cells[(i-1)*columns].getRect().y);
            p[0].x = box.x;
            p[0].y = box.y + h;
            p[1].x = box.x+w;
            p[1].y = box.y + h;
            window->setColor(border);
            SDL_RenderDrawLines(window->getRenderer(),p ,2);
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

    bool Table::update(Window* window, SDL_Event& event)
    {
        if(!isHidden())
        {
            window->setColor(fill);
            SDL_RenderFillRect(window->getRenderer(), &box);
            SDL_Point p[2];
            int h = 0;
            int w = 0;
            
            for(int i = 0; i < cells.size(); i++)
            {
                cells[i].update(window, event);
            }
            for(int i = 1; i < columns; i++)
            {
                h = box.h;
                w += (cells[i].getRect().x-box.x);
                w -= (cells[i-1].getRect().x-box.x);
                p[0].x = box.x+w;
                p[0].y = box.y;
                p[1].x = box.x+w;
                p[1].y = box.y+h;
                window->setColor(border);
                SDL_RenderDrawLines(window->getRenderer(),p ,2);
            }
            h = 0;
            w = box.w-1;
            for(int i = 1; i <= rows; i++)
            {
                h += (cells[i*columns].getRect().y-cells[(i-1)*columns].getRect().y);
                p[0].x = box.x;
                p[0].y = box.y + h;
                p[1].x = box.x+w;
                p[1].y = box.y + h;
                window->setColor(border);
                SDL_RenderDrawLines(window->getRenderer(),p ,2);
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
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {

                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
            {
                if(event.button.x >= box.x && event.button.x <= box.x+box.w)
                {
                    if(event.button.y >= box.y && event.button.y <= box.y+box.h)
                    {

                    }
                }
            }
            if(event.type == SDL_KEYDOWN)
            {
                for(int i = 0; i < cells.size(); i++)
                {
                    if(cells[i].isSelected())
                    {
                        resize();
                        break;
                    }
                }
            }
        }

        return false;
    }

}
