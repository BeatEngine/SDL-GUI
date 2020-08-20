namespace LGUI
{


class Text: public UIComponent
    {
        
        std::string fontPath;
        std::string text;
        SDL_Color foregroundColor;
        SDL_Color backgroundColor;
        SDL_Surface* textSurface;
        SDL_Rect position;
        SDL_Texture * texture;
        int sizePT;
        public:
        Text()
        {
            foregroundColor = { 255, 255, 255, 255};
            backgroundColor = { 0, 0, 0, 0};
            textSurface = 0;
            sizePT = 12;
        }
        Text(std::string fontFilePath ,int textSize, std::string text, int x, int y, int w, int h, Window* window);

        Text(std::string text, int textSize, Window* window);

        bool update(Window* window);

        bool update(Window* window, SDL_Event& event)
        {
            update(window);
        }

        void operator = (Text other)
        {
            fontPath = other.fontPath;
            text = other.text;
            foregroundColor.r = other.foregroundColor.r;
            foregroundColor.g = other.foregroundColor.g;
            foregroundColor.b = other.foregroundColor.b;
            foregroundColor.a = other.foregroundColor.a;
            backgroundColor.r = other.backgroundColor.r;
            backgroundColor.g = other.backgroundColor.g;
            backgroundColor.b = other.backgroundColor.b;
            backgroundColor.a = other.backgroundColor.a;
            //textSurface = other.textSurface;
            textSurface = 0;
            if(other.textSurface != 0)
            {
                textSurface = copySurface(other.textSurface);
            }
            position = other.position;
            texture = 0;
            if(other.texture != 0)
            {
                texture = copyTexture(other.texture);
            }
            sizePT = other.sizePT;
        }

        ~Text()
        {
            SDL_FreeSurface(textSurface);
            if(texture!=0)
            {
                SDL_DestroyTexture(texture);
            }
        }
        int getFontSize()
        {
            return sizePT;
        }
        void setText(std::string& text, SDL_Renderer* renderer, int fontSize = -1)
        {
            this->text = text;
            //setFont(fontPath, 12);
            if(fontSize < 0)
            {
                fontSize = sizePT;
            }
            sizePT = fontSize;
            position.w = text.size()*sizePT/2.150;
            position.h = sizePT*5/4;
            TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
            
            if(font)
            {
                SDL_FreeSurface(textSurface);
                TTF_SizeText(font, text.c_str(), &position.w, &position.h);
                textSurface = TTF_RenderText_Blended(font, text.c_str(), foregroundColor);
                //SDL_DestroyTexture(texture);
                texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            }
            TTF_CloseFont(font);
        }
        std::string getText()
        {
            return text;
        }
        void setBackground(RGBA color, SDL_Renderer* renderer)
        {
            backgroundColor.r = color.r;
            backgroundColor.g = color.g;
            backgroundColor.b = color.b;
            backgroundColor.a = color.a;
            //setFont(fontPath, 12);
            TTF_Font* font = TTF_OpenFont(fontPath.c_str(), sizePT);
            if(font)
            {
                SDL_FreeSurface(textSurface);
                TTF_SizeText(font, text.c_str(), &position.w, &position.h);
                textSurface = TTF_RenderText_Blended(font, text.c_str(), foregroundColor);
                //SDL_DestroyTexture(texture);
                texture = SDL_CreateTextureFromSurface(renderer, textSurface);
                TTF_CloseFont(font);
            }
            
        }

        void setPositionCenter(int x, int y)
        {
            position.x = x - position.w/2;
            position.y = y - position.h/2;
        }

        void setPosition(int x, int y)
        {
            position.x = x;
            position.y = y;
        }

        SDL_Rect& getPosition()
        {
            return position;
        }

        void setColor(RGBA color,int fontSize, SDL_Renderer* rendere)
        {
            foregroundColor.r = color.r;
            foregroundColor.g = color.g;
            foregroundColor.b = color.b;
            foregroundColor.a = color.a;
            //setFont(fontPath, 12);
            TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
            if(font)
            {
                SDL_FreeSurface(textSurface);
                TTF_SizeText(font, text.c_str(), &position.w, &position.h);
                textSurface = TTF_RenderText_Blended(font, text.c_str(), foregroundColor);
                //SDL_DestroyTexture(texture);
                texture = SDL_CreateTextureFromSurface(rendere, textSurface);
                TTF_CloseFont(font);
            }
        }

    };



}


