#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

class Sprite: public UIComponent
{

    SDL_Rect box;
    RGBA border;

    int borderSize = 0;
    std::string filePath = "";
    SDL_Surface* image = NULL;
    SDL_Texture* texture;
    bool loaded = false;
    void* onLeftClick;
    void* onRightClick;
    void* onMouseEnter;
    void* onMouseMove;
    void* onMouseLeft;
    bool mouseInside = false;
    bool mouseButtonDown = false;
    int lastMouseX = -1;
    int lastMouseY = -1;
    UIComponent* optionalParent;
    bool fitParent = false;
    bool fitBox = true;
    bool fixedAspectRatio = true;
    public:

    int getLastMouseX()
    {
        return lastMouseX;
    }

    int getLastMouseY()
    {
        return lastMouseY;
    }

    bool isLeftButtonDown()
    {
        return mouseButtonDown;
    }

    Sprite(int x, int y, int width, int hight, RGBA colorBorder, Window* window, std::string loadFromFilePath);

    Sprite(Sprite& other)
    {
        *this = other;
    }

    Sprite(Sprite* other)
    {
        *this = *other;
    }

    void operator=(Sprite& other)
    {
        box = other.getRect();
        border = other.border;
        borderSize = other.borderSize;
        filePath = other.filePath;
        onLeftClick = other.getOnLeftClick();
        onRightClick = other.getOnRightClick();
        onMouseEnter = other.getOnMouseEnter();
        onMouseMove = other.getOnMouseMove();
        onMouseLeft = other.getOnMouseLeft();
        mouseInside = other.mouseInside;
        mouseButtonDown = other.mouseButtonDown;
        lastMouseX = other.getLastMouseX();
        lastMouseY = other.getLastMouseY();
        optionalParent = other.getParentWhenSet();
        fitParent = other.fitParent;
        fitBox = other.fitBox;
        fixedAspectRatio = other.fixedAspectRatio;
        loaded = false;
        if(other.image)
        {
            int iw = 0;
            int ih = 0;
            other.getImageDimensions(&iw, &ih);
            load(other.image->pixels, other.image->pitch / other.image->w, iw, ih, 0);
        }

    }

    ~Sprite()
    {
        if(loaded)
        {
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            /*if(image)
            {
                ((SDL_Surface_Wrapper*)(image))->~SDL_Surface_Wrapper();
            }*/
        }
    }

    bool update(Window* event) override;

    bool update(Window* window, SDL_Event& event) override;

    bool load(std::string filePath, SDL_Renderer* renderer)
    {
        if(loaded)
        {
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            /*if(image)
            {
                ((SDL_Surface_Wrapper*)(image))->~SDL_Surface_Wrapper();
            }*/
        }
        FILE* f = fopen(filePath.c_str(), "rb");
        if(!f)
        {
            printf( "File not found: %s\n", filePath.c_str());
            loaded = false;
            return false;
        }
        

        int req_format = STBI_rgb_alpha;
        int width, height, orig_format;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &orig_format, req_format);
        if(data == 0)
        {
            printf("Failed to load image. STBI-Error:%s\n", stbi_failure_reason());
            loaded = false;
            return false;
        }
        // Only STBI_rgb (3) and STBI_rgb_alpha (4) are supported here!
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
        amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
        #endif

        int depth, pitch;
        if (req_format == STBI_rgb)
        {
            depth = 24;
            pitch = 3*width;
        }
        else
        {
            depth = 32;
            pitch = 4*width;
        }
        image = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch, rmask, gmask, bmask, amask);
        if (image == 0) {
            SDL_Log("Creating surface failed: %s", SDL_GetError());
            stbi_image_free(data);
            loaded = false;
            return false;
        }
        texture = SDL_CreateTextureFromSurface(renderer, image);
        stbi_image_free(data);
        loaded = true;
        return true;
    }

    bool load(void* data, size_t bytesPerPixel, int width, int height, SDL_Renderer* renderer)
    {
        if(loaded)
        {
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            /*if(image)
            {
                ((SDL_Surface_Wrapper*)(image))->~SDL_Surface_Wrapper();
            }*/
        }
        if(data == 0)
        {
            loaded = false;
            return false;
        }
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
        amask = (bytesPerPixel == STBI_rgb) ? 0 : 0xff000000;
        #endif
        image = SDL_CreateRGBSurfaceFrom((void*)data, width, height, bytesPerPixel*8, bytesPerPixel*width, rmask, gmask, bmask, amask);
        if (image == 0) {
            SDL_Log("Creating surface failed: %s", SDL_GetError());
            stbi_image_free(data);
            loaded = false;
            return false;
        }
        if(renderer)
        {
            texture = SDL_CreateTextureFromSurface(renderer, image);
        }
        else
        {
            texture = 0;
        }
        return true;
    }

    void getImageDimensions(int* width, int* hight)
    {
        *width = image->w;
        *hight = image->h;
    }

    void setBorder(RGBA color, int size = 1)
    {
        border = color;
        borderSize = size;
    }

    void setPosition(int x, int y)
    {
        if(x < 0)
        {
            x = 0;
        }
        if(y < 0)
        {
            y = 0;
        }
        box.x = x;
        box.y = y;
    }

    void setPosition(int x, int y, bool center,  Window* window);

    void setSize(int width, int hight)
    {
        box.w = width;
        box.h = hight;
    }

    void setFitRules(bool fitParent, bool fitBox = true, bool fixedAspectRatio = true, UIComponent* parentSet = 0)
    {
        if(parentSet)
        {
            setParent(parentSet);
        }
        this->fitParent = fitParent;
        this->fixedAspectRatio = fixedAspectRatio;
        this->fitBox = fitBox;
    }

    unsigned int getBorderSize()
    {
        return borderSize;
    }

    SDL_Rect& getRect()
    {
        return box;
    }

    SDL_Rect& getPosition()
    {
        return box;
    }

    void setLastCursorPosition(int x, int y)
    {
        lastMouseX = x;
        lastMouseY = y;
    }

    SDL_Rect getPositionScaled(Window* window);

    void setOnLeftClick(void (*event)(void** parameters))
    {
        onLeftClick = (void*)(event);
    }

    void setOnRightClick(void (*event)(void** parameters))
    {
        onRightClick = (void*)(event);
    }

    void setOnMouseEnter(void (*event)(void** parameters))
    {
        onMouseEnter = (void*)(event);
    }

    void setOnMouseLeft(void (*event)(void** parameters))
    {
        onMouseLeft = (void*)(event);
    }

    void setOnMouseMove(void (*event)(void** parameters))
    {
        onMouseMove = (void*)(event);
    }

    UIComponent* getParentWhenSet()
    {
        return optionalParent;
    }

    void setParent(UIComponent* parent)
    {
        optionalParent = parent;
    }

    void* getOnLeftClick()
    {
        return onLeftClick;
    }

    void* getOnRightClick()
    {
        return onRightClick;
    }

    void* getOnMouseEnter()
    {
        return onMouseEnter;
    }

    void* getOnMouseLeft()
    {
        return onMouseLeft;
    }

    void* getOnMouseMove()
    {
        return onMouseMove;
    }

};

