
namespace LGUI
{

    bool Text::update(Window* window)
    {
        if(text.length()>0 && !isHidden())
        {
            if(SDL_RenderCopy(window->getRenderer(), texture, NULL, &position) != 0)
            {
                printf("Text: SDL-Error: %s\n", SDL_GetError());
            }
        }
        return false;
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
        textSurface = TTF_RenderText_Blended(font, text.c_str(), foregroundColor);
        texture = SDL_CreateTextureFromSurface(window->getRenderer(), textSurface);
        TTF_CloseFont(font);
    }

    }
