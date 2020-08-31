namespace LGUI
{

    void TableColumn::addRow(std::string& text, Window* window, int textSize)
    {
        fields.push_back(InputBox(x, y+getHight(), 50, 20, text, background, border, window, textSize));
        fields.back().setBorder(border,0);
    }

    std::string TableColumn::getText(int row)
    {
        if(row < fields.size())
        {
            return fields.at(row).getText();
        }
        return "";
    }

    int TableColumn::getWidth()
    {
        int max = 0;
        for(int i = 0; i < fields.size(); i++)
        {
            if(fields.at(i).getRect().w > max)
            {
                max = fields.at(i).getRect().w;
            }
        }
        width = max;
        return max;
    }

    void TableColumn::setText(int row, std::string& text, SDL_Renderer* renderer, int textSize)
    {
        if(row < fields.size())
        {
            fields.at(row).setText(text, renderer, textSize);
            width = fields.at(row).getRect().w;
        }
    }

    void TableColumn::addRow(Window* window, int textSize)
    {
        std::string s = " ";
        addRow(s, window, textSize);
    }

    bool TableColumn::update(Window* window)
    {
        if(!isHidden())
        {
            SDL_Point p[2];
            int w = getWidth();
            int h = 0;
            for(int i = 0; i < fields.size(); i++)
            {
                fields.at(i).update(window);
                h += fields.at(i).getRect().h;
                p[0].x = x;
                p[0].y = y + h;
                p[1].x = x + w;
                p[1].y = y + h;
                window->setColor(border);
                if(i + 1 < fields.size())
                {
                    //SDL_RenderDrawLines(window->getRenderer(), p, 2);
                    SDL_Rect rec = {p[0].x, p[1].y, w, 1};
                    SDL_RenderDrawRect(window->getRenderer(), &rec);
                }
            }
            return true;
        }
        return false;
    }

    bool TableColumn::update(Window* window, SDL_Event& event)
    {
        if(!isHidden() && !isEnabled())
        {
            return update(window);
        }
        if(isEnabled())
        {
            SDL_Point p[2];
            int w = getWidth();
            int h = 0;
            for(int i = 0; i < fields.size(); i++)
            {
                fields.at(i).update(window, event);
                h += fields.at(i).getRect().h;
                p[0].x = x;
                p[0].y = y + h;
                p[1].x = x + w;
                p[1].y = y + h;
                window->setColor(border);
                if(i + 1 < fields.size())
                {
                    SDL_RenderDrawLines(window->getRenderer(), p, 2);
                }
            }
            return true;
        }
        return false;
    }

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
        
        for(int i = 0; i < columns.size(); i++)
        {
            columns.at(i).update(window);
            h = columns.at(i).getHight();
            w = columns.at(i).getWidth();
            p[0].x = box.x+w;
            p[0].y = box.y;
            p[1].x = box.x+w;
            p[1].y = box.y+h;
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
            
            for(int i = 0; i < columns.size(); i++)
            {
                columns.at(i).update(window, event);
                h = columns.at(i).getHight();
                w = columns.at(i).getWidth();
                p[0].x = box.x+w;
                p[0].y = box.y;
                p[1].x = box.x+w;
                p[1].y = box.y+h;
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
        }

        return false;
    }

}
