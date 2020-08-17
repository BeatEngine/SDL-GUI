#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <string>

#include <unistd.h>

#include <stdio.h>

namespace LGUI
{

    class SDL_SW_YUVTexture_Wrapper
    {
        public:
        SDL_SW_YUVTexture_Wrapper()
        {

        }
        Uint32 format;
        Uint32 target_format;
        int w, h;
        Uint8 *pixels;
        /* These are just so we don't have to allocate them separately */
        Uint16 pitches[3];
        Uint8 *planes[3];
        /* This is a temporary surface in case we have to stretch copy */
        SDL_Surface *stretch;
        SDL_Surface *display;
        ~SDL_SW_YUVTexture_Wrapper()
        {
            free(pixels);
        }
    };

    class SDL_Texture_Wrapper
    {
        public:
        SDL_Texture_Wrapper()
        {

        }
        const void *magic;
        Uint32 format;              /**< The pixel format of the texture */
        int access;                 /**< SDL_TextureAccess */
        int w;                      /**< The width of the texture */
        int h;                      /**< The height of the texture */
        int modMode;                /**< The texture modulation mode */
        SDL_BlendMode blendMode;    /**< The texture blend mode */
        SDL_ScaleMode scaleMode;    /**< The texture scale mode */
        Uint8 r, g, b, a;           /**< Texture modulation values */

        SDL_Renderer *renderer;

        /* Support for formats not supported directly by the renderer */
        SDL_Texture *native;
        SDL_SW_YUVTexture_Wrapper *yuv;
        void *pixels;
        int pitch;
        SDL_Rect locked_rect;
        SDL_Surface *locked_surface;  /**< Locked region exposed as a SDL surface */

        Uint32 last_command_generation; /* last command queue generation this texture was in. */

        void *driverdata;           /**< Driver specific texture representation */

        SDL_Texture *prev;
        SDL_Texture *next;

    };

    class SDL_BlitInfo_wrapper
    {
        public:
        Uint8 *src;
        int src_w, src_h;
        int src_pitch;
        int src_skip;
        Uint8 *dst;
        int dst_w, dst_h;
        int dst_pitch;
        int dst_skip;
        SDL_PixelFormat *src_fmt;
        SDL_PixelFormat *dst_fmt;
        Uint8 *table;
        int flags;
        Uint32 colorkey;
        Uint8 r, g, b, a;
    };

    class SDL_BlitMap_Wrapper
    {
        public:
        SDL_BlitMap_Wrapper()
        {

        }
        SDL_BlitMap_Wrapper(SDL_BlitMap_Wrapper* other)
        {
            this->dst = other->dst;
            identity = other->identity;
            blit = other->blit;
            data = other->data;
            info = other->info;
            dst_palette_version = other->dst_palette_version;
            src_palette_version = other->src_palette_version;
        }
        SDL_Surface *dst;
        int identity;
        SDL_blit blit;
        void *data;
        SDL_BlitInfo_wrapper info;
        /* the version count matches the destination; mismatch indicates
        an invalid mapping */
        Uint32 dst_palette_version;
        Uint32 src_palette_version;
    };

    class SDL_Surface_Wrapper
    {
        public:
        SDL_Surface_Wrapper()
        {

        }
        ~SDL_Surface_Wrapper()
        {
            //free(pixels);
            //delete map;
        }
        Uint32 flags;               /**< Read-only */
        SDL_PixelFormat *format;    /**< Read-only */
        int w, h;                   /**< Read-only */
        int pitch;                  /**< Read-only */
        void *pixels;               /**< Read-write */
        /** Application data associated with the surface */
        void *userdata;             /**< Read-write */
        /** information needed for surfaces requiring locks */
        int locked;                 /**< Read-only */
        void *lock_data;            /**< Read-only */
        /** clipping information */
        SDL_Rect clip_rect;         /**< Read-only */
        /** info for fast blit mapping to other surfaces */
        SDL_BlitMap_Wrapper *map;    /**< Private */
        /** Reference count -- used when freeing surface */
        int refcount;  
    };

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

    SDL_Surface* copySurface(SDL_Surface* surface)
    {
        SDL_Surface_Wrapper* other = (SDL_Surface_Wrapper*)surface;
        SDL_Surface_Wrapper* tx = new SDL_Surface_Wrapper();

        tx->clip_rect = other->clip_rect;
        tx->flags = 1;
        tx->format = other->format;
        tx->h = other->h;
        tx->lock_data = other->lock_data;
        tx->locked = other->locked;
        tx->pitch = other->pitch;
        tx->refcount = other->refcount;
        tx->userdata = other->userdata;
        tx->pixels = (Uint8*)calloc(tx->w * tx->h, 4);
        memcpy(tx->pixels, other->pixels, 4 * tx->w * tx->h);
        tx->map = new SDL_BlitMap_Wrapper(other->map);
        return (SDL_Surface*)tx;
    }

    SDL_Texture* copyTexture(SDL_Texture* texture)
    {
        //SDL_Texture* tx = (SDL_Texture*)calloc(1, (28+sizeof(int)*5+sizeof(void*)*9)*2/3);
        SDL_Texture_Wrapper* other = (SDL_Texture_Wrapper*)texture;
        SDL_Texture_Wrapper* tx = new SDL_Texture_Wrapper();

        tx->modMode = other->modMode;
        tx->pitch = other->pitch;
        tx->r = other->r;
        tx->scaleMode = other->scaleMode;
        tx->w = other->w;

        tx->a = other->a;
        tx->access = other->access;
        tx->b = other->b;
        tx->blendMode = other->blendMode;
        tx->format = other->format;
        tx->g = other->g;
        tx->h = other->h;
        tx->last_command_generation = other->last_command_generation;
        tx->locked_rect = other->locked_rect;

        tx->magic = other->magic;
        tx->renderer = other->renderer;
        tx->native = ((SDL_Texture*)tx);
        tx->locked_surface = other->locked_surface;
        tx->driverdata = other->driverdata;
        tx->prev = other->prev;
        tx->next = other->next;
        if(other->yuv != 0)
        {
            tx->yuv = new SDL_SW_YUVTexture_Wrapper;
            tx->yuv->format = other->yuv->format;
            tx->yuv->h = other->yuv->h;
            tx->yuv->pitches[0] = other->yuv->pitches[0];
            tx->yuv->pitches[1] = other->yuv->pitches[1];
            tx->yuv->pitches[2] = other->yuv->pitches[2];
            tx->yuv->target_format = other->yuv->target_format;
            tx->yuv->w = other->yuv->w;

            tx->yuv->pixels = (Uint8*)calloc(tx->yuv->w * tx->yuv->h, 4);
            memcpy(tx->yuv->pixels, other->yuv->pixels, 4 * tx->yuv->w * tx->yuv->h);
            tx->yuv->stretch = other->yuv->stretch;
            tx->yuv->display = other->yuv->display;
        }
        else
        {
            tx->yuv = 0;
        }
        
        return (SDL_Texture*)tx;
    }

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

        bool update(Window* window);

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
            textSurface = copySurface(other.textSurface);
            position = other.position;
            texture = copyTexture(other.texture);
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
            TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
            if(font)
            {
                SDL_FreeSurface(textSurface);
                textSurface = TTF_RenderText_Shaded(font, text.c_str(), foregroundColor, backgroundColor);
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
                textSurface = TTF_RenderText_Shaded(font, text.c_str(), foregroundColor, backgroundColor);
                //SDL_DestroyTexture(texture);
                texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            }
            TTF_CloseFont(font);
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
                textSurface = TTF_RenderText_Shaded(font, text.c_str(), foregroundColor, backgroundColor);
                //SDL_DestroyTexture(texture);
                texture = SDL_CreateTextureFromSurface(rendere, textSurface);
            }
            TTF_CloseFont(font);
        }

    };

    class Button: public UIComponent
    {

        SDL_Rect box;
        Text text;
        RGBA fill;
        RGBA border;

        

        void* onLeftClick;
        void* onRightClick;
        public:

        Button(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize);

        bool update(Window* event) override;

        bool update(Window* window, SDL_Event& event) override;

        void setText(std::string& text, SDL_Renderer* renderer, int fontSize = -1)
        {
            this->text.setText(text, renderer, fontSize);
        }

        int getTextSize()
        {
            return text.getFontSize();
        }

        void setTextColor(RGBA color, int fontSize, SDL_Renderer* renderer)
        {
            text.setColor(color, fontSize, renderer);
        }

        std::string getText()
        {
            return this->text.getText();
        }

        void setOnLeftClick(void (*event)(void** parameters))
        {
            onLeftClick = (void*)(event);
        }

        void setOnRightClick(void (*event)(void** parameters))
        {
            onRightClick = (void*)(event);
        }

    };

    class Window
    {

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        std::vector<UIComponent*> components;
        unsigned long framedelay;
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
            framedelay = 1000/fps;
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
            //update();
            //updateScreen();
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
            //SDL_UpdateWindowSurface(window);
            SDL_RenderPresent(renderer);
            usleep(framedelay);
        }      


        bool update()
        {
            bool refresh = false;
            setColor(RGBA(255,255,255,255));
            clearBackground();
            
            if (SDL_PollEvent(&event))
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
            else
            {
                for(int i = 0; i < components.size(); i++)
                {
                    if(components.at(i)->update(this))
                    {
                        refresh = true;
                    }
                }
            }
            

            
            

            if(refresh)
            {
                updateScreen();
            }
            //usleep(framedelay);
            return true;
        }


    };

    bool Button::update(Window* window)
    {
        window->setColor(fill);
        SDL_RenderFillRect(window->getRenderer(), &box);
        text.update(window);
    }

    bool Button::update(Window* window, SDL_Event& event)
    {
        window->setColor(fill);
        SDL_RenderFillRect(window->getRenderer(), &box);
        text.update(window);

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

        return false;
    }

    bool Text::update(Window* window)
    {
        if(SDL_RenderCopy(window->getRenderer(), texture, NULL, &position) != 0)
        {
            printf("SDL-Error: %s\n", SDL_GetError());
        }
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
        textSurface = TTF_RenderText_Shaded(font, text.c_str(), foregroundColor, backgroundColor);
        texture = SDL_CreateTextureFromSurface(window->getRenderer(), textSurface);
        TTF_CloseFont(font);
    }

    Button::Button(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize = 12)
    {
        onRightClick = NULL;
        onLeftClick = NULL;
        box.x = x;
        box.y = y;
        box.w = width;
        box.h = hight;
        fill = colorFill;
        border = colorBorder;
        this->text = Text("./Arial.ttf", textSize, text, x+width/2-text.size()*textSize/4.30, y+(textSize*4/3)/2, text.size()*textSize/2.150, textSize*5/4, window);
        this->text.setBackground(fill, window->getRenderer());
    }

    















}

