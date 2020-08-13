#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <string>

namespace LGUI
{

    class RGBA
    {
        public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        RGBA()
        {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
        }
        RGBA(uint8_t red,uint8_t green,uint8_t blue,uint8_t alpha)
        {
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }

        void operator = (RGBA& other)
        {
            r = other.r;
            g = other.g;
            b = other.g;
            a = other.a;
        }
    };

    class Window;

    class UIComponent
    {
        unsigned int id;
        public:

        virtual bool update(Window* window)
        {
            return false;
        }

        virtual bool update(Window* window, SDL_Event& event)
        {
            return false;
        }

        void setId(unsigned int id)
        {
            this->id = id;
        }

        unsigned int getId()
        {
            return id;
        }

    };

    class Text: public UIComponent
    {
        TTF_Font* font;
        std::string text;
        SDL_Color foregroundColor;
        SDL_Color backgroundColor;
        SDL_Surface* textSurface;
        SDL_Rect position;
        SDL_Texture * texture;
        public:
        Text()
        {
            foregroundColor = { 255, 255, 255, 255};
            backgroundColor = { 0, 0, 0, 0};
            font = 0;
            textSurface = 0;
        }
        Text(std::string font ,int textSize, std::string text, int x, int y, Window* window);

        bool update(Window* window);

        void operator = (Text other)
        {
            font = other.font;
            text = other.text;
            foregroundColor.r = other.foregroundColor.r;
            foregroundColor.g = other.foregroundColor.g;
            foregroundColor.b = other.foregroundColor.b;
            foregroundColor.a = other.foregroundColor.a;
            backgroundColor.r = other.backgroundColor.r;
            backgroundColor.g = other.backgroundColor.g;
            backgroundColor.b = other.backgroundColor.b;
            backgroundColor.a = other.backgroundColor.a;
            textSurface = other.textSurface;
            position = other.position;
            texture = other.texture;
        }

        ~Text()
        {
            if(font!=0)
            {
                //TTF_CloseFont(font);
            }
            if(textSurface!=0)
            {
                //SDL_FreeSurface(textSurface);
            }
        }
        void setFont(std::string& font ,int textSize)
        {
            this->font = TTF_OpenFont(font.c_str(), textSize);
        }
        void setText(std::string& text)
        {
            this->text = text;
        }
        std::string getText()
        {
            return text;
        }
        void setBackground(RGBA color, SDL_Renderer* rendere)
        {
            backgroundColor.r = color.r;
            backgroundColor.g = color.g;
            backgroundColor.b = color.b;
            backgroundColor.a = color.a;
            if(textSurface)
            {
                SDL_FreeSurface(textSurface);
            }
            if(font)
            {
                textSurface = TTF_RenderText_Shaded(font, text.c_str(), foregroundColor, backgroundColor);
                if(texture)
                {
                    SDL_DestroyTexture(texture);
                }
                texture = SDL_CreateTextureFromSurface(rendere, textSurface);
            }
        }
        void setColor(RGBA color, SDL_Renderer* rendere)
        {
            foregroundColor.r = color.r;
            foregroundColor.g = color.g;
            foregroundColor.b = color.b;
            foregroundColor.a = color.a;
            if(textSurface)
            {
                SDL_FreeSurface(textSurface);
            }
            if(font)
            {
                textSurface = TTF_RenderText_Shaded(font, text.c_str(), foregroundColor, backgroundColor);
                if(texture)
                {
                    SDL_DestroyTexture(texture);
                }
                texture = SDL_CreateTextureFromSurface(rendere, textSurface);
            }
        }

    };

    class Button: public UIComponent
    {

        SDL_Rect box;
        Text text;
        RGBA fill;
        RGBA border;
        public:

        Button(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize);

        bool update(Window* window, SDL_Event& event) override;

        void setText(std::string& text)
        {
            this->text.setText(text);
        }

        void setTextColor(RGBA color, SDL_Renderer* renderer)
        {
            text.setColor(color, renderer);
        }

        std::string getText()
        {
            return this->text.getText();
        }

    };

    class Window
    {

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        std::vector<UIComponent*> components;

        public:


        SDL_Renderer* getRenderer()
        {
            return renderer;
        }

        SDL_Window* getWindow()
        {
            return window;
        }

        Window(std::string& title, int width, int hight, int fps = 60)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
                printf("Error initializing SDL: %s\n", SDL_GetError()); 
            }
            TTF_Init();

            window = SDL_CreateWindow(title.c_str(), 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       width, hight, 0); 
            renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_Delay(1000/fps);
            setColor(255, 255, 255, 255);
            clearBackground();
            updateScreen();
        }

        ~Window()
        {
            while(components.size() > 0)
            {
                delete components.back();
                components.pop_back();
            }
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
        }

        void addComponent(UIComponent* component)
        {
            components.push_back(component);
            update();
            updateScreen();
        }

        void setWindowMode(SDL_DisplayMode* mode)
        {
            SDL_SetWindowDisplayMode(window, mode);
        }
        void setFullscreen(bool enable, bool borderlessWindowFullscreen)
        {
            if(enable)
            {
                if(borderlessWindowFullscreen)
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                else
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
            }
            SDL_SetWindowFullscreen(window, 0);
        }
        void setPosition(int x, int y)
        {
            SDL_SetWindowPosition(window, x, y);
        }
        void setSize(int width, int hight)
        {
            SDL_SetWindowSize(window, width, hight);
        }
        void setResizable(bool resizable)
        {
            SDL_SetWindowResizable(window, (SDL_bool)resizable);
        }
        void setTitle(std::string& title)
        {
            SDL_SetWindowTitle(window, title.c_str());
        }

        void setBordered(bool bordered)
        {
            SDL_SetWindowBordered(window, (SDL_bool)(bordered));
        }

        void setShape(SDL_Surface* shape, SDL_WindowShapeMode* mode)
        {
            SDL_SetWindowShape(window, shape, mode);
        }

        void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
        {
            SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        }
        void setColor(RGBA color)
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        }

        void clearBackground()
        {
            SDL_RenderClear(renderer);
        }


        void updateScreen()
        {
            SDL_UpdateWindowSurface(window);
            SDL_RenderPresent(renderer);
        }      


        bool update()
        {
            bool refresh = false;
            setColor(RGBA(255,255,255,255));
            clearBackground();
            
            while (SDL_PollEvent(&event))
            { 
                for(int i = 0; i < components.size(); i++)
                {
                    if(components.at(i)->update(this, event))
                    {
                        refresh = true;
                    }
                }
                if(event.type ==  SDL_QUIT)
                {
                    // handling of close button 
                    return false;
                }
            }

            for(int i = 0; i < components.size(); i++)
            {
                if(components.at(i)->update(this))
                {
                    refresh = true;
                }
            }
            

            if(refresh)
            {
                updateScreen();
            }
            return true;
        }


    };

    bool Button::update(Window* window, SDL_Event& event)
    {
        window->setColor(fill);
        SDL_RenderFillRect(window->getRenderer(), &box);
        text.update(window);

        if(event.type == SDL_MOUSE_TOUCHID || event.type == SDL_KEYDOWN)
        {
            return true;
        }

        return false;
    }

    bool Text::update(Window* window)
    {
        SDL_RenderCopy(window->getRenderer(), texture, NULL, &position);
    }

    Text::Text(std::string font ,int textSize, std::string text, int x, int y, Window* window)
    {
        foregroundColor = { 255, 255, 255, 255};
        backgroundColor = { 255, 255, 255, 0};
        setFont(font, textSize);
        this->text = text;
        position.h = textSize + 1;
        position.w = text.length()*5+1;
        position.x = x;
        position.y = y;
        textSurface = TTF_RenderText_Shaded(this->font, text.c_str(), foregroundColor, backgroundColor);
        texture = SDL_CreateTextureFromSurface(window->getRenderer(), textSurface);
    }

    Button::Button(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize = 12)
    {
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        fill = colorFill;
        border = colorBorder;
        this->text = Text("./Arial.ttf", textSize, text, x+width-text.size()*textSize/2+1, y+textSize/2, window);
        this->text.setBackground(fill, window->getRenderer());
    }

















}



