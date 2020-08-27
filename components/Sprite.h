#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

namespace LGUI
{


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
        UIComponent* optionalParent;
        public:

        Sprite(int x, int y, int width, int hight, RGBA colorBorder, Window* window, std::string loadFromFilePath);

        ~Sprite()
        {
            if(loaded)
            {
                SDL_DestroyTexture(texture);
                if(image)
                {
                    ((SDL_Surface_Wrapper*)(image))->~SDL_Surface_Wrapper();
                }
            }
        }

        bool update(Window* event) override;

        bool update(Window* window, SDL_Event& event) override;

        bool load(std::string filePath, SDL_Renderer* renderer)
        {
            if(loaded)
            {
                SDL_DestroyTexture(texture);
                if(image)
                {
                    ((SDL_Surface_Wrapper*)(image))->~SDL_Surface_Wrapper();
                }
            }
            FILE* f = fopen(filePath.c_str(), "rb");
            if(!f)
            {
                printf( "File not found: %s\n", filePath.c_str());
                loaded = false;
                return false;
            }

            int channels = 0;
            int x = 0;
            int y = 0;
            SDL_Surface_Wrapper* swapper = new SDL_Surface_Wrapper();
            void* pixels = stbi_load_from_file(f, &x, &y, &channels, STBI_rgb_alpha);
            if(!pixels)
            {
                printf( "File loading error: %s\n", filePath.c_str());
                loaded = false;
                return false;
            }
            swapper->w = x;
            swapper->h = y;
            swapper->pixels = pixels;
            swapper->format = new SDL_PixelFormat_Wrapper(channels, channels);
            image = (SDL_Surface*)swapper;
            return true;
        }

        bool load(void* data, size_t bytesPerPixel, int width, int hight, SDL_Renderer* renderer)
        {
            if(loaded)
            {
                SDL_DestroyTexture(texture);
                if(image)
                {
                    ((SDL_Surface_Wrapper*)(image))->~SDL_Surface_Wrapper();
                }
            }
            if(data == 0)
            {
                loaded = false;
                return false;
            }
            SDL_Surface_Wrapper* swapper = new SDL_Surface_Wrapper();
            if(!data)
            {
                printf( "Sprite load fails (data is NULL)\n");
                loaded = false;
                return false;
            }
            swapper->w = width;
            swapper->h = hight;
            memcpy(swapper->pixels, data, bytesPerPixel*width*hight);
            swapper->format = new SDL_PixelFormat_Wrapper(bytesPerPixel, bytesPerPixel);
            image = (SDL_Surface*)swapper;
            return true;
        }

        void setBorder(RGBA color, int size = 1)
        {
            border = color;
            borderSize = size;
        }

        void setPosition(int x, int y)
        {
            box.x = x;
            box.y = y;
        }

        void setSize(int width, int hight)
        {
            box.w = width;
            box.h = hight;
        }

        unsigned int getBorderSize()
        {
            return borderSize;
        }

        SDL_Rect& getRect()
        {
            return box;
        }

        void setOnLeftClick(void (*event)(void** parameters))
        {
            onLeftClick = (void*)(event);
        }

        void setOnRightClick(void (*event)(void** parameters))
        {
            onRightClick = (void*)(event);
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

    };

}


