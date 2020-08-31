
namespace LGUI
{

    bool Text::update(Window* window)
    {
        if(textSurface != 0 && texture == 0)
        {
            texture = SDL_CreateTextureFromSurface(window->getRenderer(), textSurface);
        }
        if(text.length()>0 && !isHidden())
        {
            if(rectIsInBorders(position))
            {
                if(SDL_RenderCopy(window->getRenderer(), texture, NULL, &position) != 0)
                {
                    printf("Text: SDL-Error: %s\n", SDL_GetError());
                }
            }
            else
            {
                SDL_Rect cropped = cropToDrawBorders(position);
                if(SDL_RenderCopy(window->getRenderer(), texture, &cropped, &position) != 0)
                {
                    printf("Text: SDL-Error: %s\n", SDL_GetError());
                }
            }
        }
        return false;
    }

    Text::Text(std::string text, int textSize, Window* window)
    {
        
        foregroundColor = { 0, 0, 0, 255};
        backgroundColor = { 255, 255, 255, 0};
        fontPath = "Arial.ttf";
        this->text = text;
        sizePT = textSize;
        position.h = 20;
        position.w = 100;
        position.x = 50;
        position.y = 50;
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), textSize);
        if(text.length() < 1)
        {
            this->text = "";
            text = "  ";
        }
        TTF_SizeText(font, text.c_str(), &position.w, &position.h);
        setPosition(position.x, position.y);
        textSurface = TTF_RenderText_Blended(font, text.c_str(), foregroundColor);
        texture = SDL_CreateTextureFromSurface(window->getRenderer(), textSurface);
        TTF_CloseFont(font);
        update(window);
    }

    Text::Text(std::string fontFilePath ,int textSize, std::string text, int x, int y, int w, int h, Window* window)
    {
        
        foregroundColor = { 0, 0, 0, 255};
        backgroundColor = { 255, 255, 255, 0};
        fontPath = fontFilePath;
        this->text = text;
        sizePT = textSize;
        position.h = h;
        position.w = w;
        position.x = x;
        position.y = y;
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), textSize);
        if(text.length() < 1)
        {
            this->text = "";
            text = "  ";
        }
        TTF_SizeText(font, text.c_str(), &position.w, &position.h);
        setPosition(x, y);
        textSurface = TTF_RenderText_Blended(font, text.c_str(), foregroundColor);
        texture = SDL_CreateTextureFromSurface(window->getRenderer(), textSurface);
        TTF_CloseFont(font);
    }

    }
