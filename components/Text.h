
class Text: public UIComponent
{
    
    std::string fontPath = "";
    std::string text;
    SDL_Color foregroundColor;
    SDL_Color backgroundColor;
    SDL_Surface* textSurface;
    SDL_Rect position;
    SDL_Texture * texture = 0;
    int sizePT;
    public:
    Text()
    {
        foregroundColor = { 255, 255, 255, 255};
        backgroundColor = { 0, 0, 0, 0};
        textSurface = 0;
        sizePT = 12;
        position.h = 20;
        position.w = 100;
        position.x = 0;
        position.y = 0;
    }

    Text(Text* other)
    {
        *this = *other;
    }

    Text(const Text& other)
    {
        //*this = other;
        fontPath = other.fontPath;
        text = other.text;
        foregroundColor = other.foregroundColor;
        backgroundColor = other.backgroundColor;
        position = other.position;
        sizePT = other.sizePT;
        textSurface = 0;
        texture = 0;
        if(other.textSurface)
        {
            int form = other.textSurface->pitch/other.textSurface->w;
            Uint32 rmask, gmask, bmask, amask;
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            int shift = (req_format == STBI_rgb) ? 8 : 0;
            rmask = 0xff000000 >> shift;
            gmask = 0x00ff0000 >> shift;
            bmask = 0x0000ff00 >> shift;
            amask = 0x000000ff >> shift;
            #else // little endian, like x86
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = (form == STBI_rgb) ? 0 : 0xff000000;
            #endif
            textSurface = SDL_CreateRGBSurfaceFrom(other.textSurface->pixels, other.textSurface->w, other.textSurface->h, form*8, other.textSurface->w*form, rmask, gmask, bmask,amask);
        }
    }

    Text(std::string fontFilePath ,int textSize, std::string text, int x, int y, int w, int h, Window* window);

    Text(std::string text, int textSize, Window* window);

    bool update(Window* window);

    bool update(Window* window, SDL_Event& event)
    {
        return update(window);
    }

    void setFontPath(std::string filePath)
    {
        fontPath = filePath;
    }

    bool hasPosition() override
    {
        return true;
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
        texture = 0;
        position = other.position;
        if(other.textSurface != 0)
        {
            int tmpChannels = (other.textSurface->pitch)/(other.textSurface->w);
            Uint32 rmask, gmask, bmask, amask;

            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
                int shift = (req_format == STBI_rgb) ? 8 : 0;
                rmask = 0xff000000 >> shift;
                gmask = 0x00ff0000 >> shift;
                bmask = 0x0000ff00 >> shift;
                amask = 0x000000ff >> shift;
            #else // little endian, like x86
                rmask = 0x000000ff;
                gmask = 0x0000ff00;
                bmask = 0x00ff0000;
                amask = (tmpChannels == STBI_rgb) ? 0 : 0xff000000;
            #endif
            textSurface = SDL_CreateRGBSurfaceFrom(other.textSurface->pixels, other.textSurface->w, other.textSurface->h, tmpChannels*8, other.textSurface->pitch, rmask, gmask, bmask, amask);
        }

        /*if(other.textSurface != 0)
        {
            textSurface = copySurface(other.textSurface);
        }
        position = other.position;
        texture = 0;
        if(other.texture != 0)
        {
            texture = copyTexture(other.texture);
        }*/
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
        if(text.length() < 1)
        {
            this->text = "";
            text = "  ";
        }
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
            if(this->text.length()>0)
            {
                TTF_SizeText(font, text.c_str(), &position.w, &position.h);
            }
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

    std::string& getFontPath()
    {
        return fontPath;
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

    void setPosition(int x, int y) override
    {
        position.x = x;
        position.y = y;
    }

    SDL_Rect& getPosition() override
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
