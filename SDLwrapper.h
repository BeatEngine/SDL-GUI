#include <SDL2/SDL.h>

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

    class SDL_Color_Wrapper
    {
        public:

        SDL_Color_Wrapper()
        {

        }
        SDL_Color_Wrapper(SDL_Color_Wrapper* other)
        {
            r = other->r;
            g = other->g;
            b = other->b;
            a = other->a;
        }

        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
    };

    class SDL_Palette_Wrapper
    {
        public:
        int ncolors;
        SDL_Color_Wrapper *colors;
        Uint32 version;
        int refcount;
        SDL_Palette_Wrapper()
        {
            colors = 0;
        }
        ~SDL_Palette_Wrapper()
        {
            if(colors)
            {
                delete colors;
            }
        }
        SDL_Palette_Wrapper(SDL_Palette_Wrapper* other)
        {
            ncolors = other->ncolors;
            version = other->version;
            refcount = other->refcount;
            colors = new SDL_Color_Wrapper(other->colors);
        }

        
    };

    class SDL_PixelFormat_Wrapper
    {
        public:
        SDL_PixelFormat_Wrapper(int bytesPerPixel, int format)
        {
            this->format = format;
            this->BitsPerPixel = bytesPerPixel*8;
            this->BytesPerPixel = bytesPerPixel;
            padding[0] = 0;
            padding[1] = 0;
            Uint32 rmask, gmask, bmask, amask;
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            int shift = (format == 3) ? 8 : 0;
            rmask = 0xff000000 >> shift;
            gmask = 0x00ff0000 >> shift;
            bmask = 0x0000ff00 >> shift;
            amask = 0x000000ff >> shift;
            #else // little endian, like x86
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
            #endif
            Rmask = rmask;
            Gmask = gmask;
            Bmask = bmask;
            Amask = amask;
            Rloss = 0;
            Gloss = 0;
            Bloss = 0;
            Aloss = 0;
            Rshift = 0;
            Gshift = 0;
            Bshift = 0;
            Ashift = 0;
            refcount = 0;
            next = 0;
            palette = 0;
        }
        SDL_PixelFormat_Wrapper(SDL_PixelFormat_Wrapper* other)
        {
            format = other->format;
            BitsPerPixel = other->BitsPerPixel;
            BytesPerPixel = other->BytesPerPixel;
            padding[0] = other->padding[0];
            padding[1] = other->padding[1];
            Rmask = other->Rmask;
            Gmask = other->Gmask;
            Bmask = other->Bmask;
            Amask = other->Amask;
            Rloss = other->Rloss;
            Gloss = other->Gloss;
            Bloss = other->Bloss;
            Aloss = other->Aloss;
            Rshift = other->Rshift;
            Gshift = other->Gshift;
            Bshift = other->Bshift;
            Ashift = other->Ashift;
            refcount = other->refcount;
            if(other->next)
            {
                next = new SDL_PixelFormat_Wrapper(other->next);
            }
            else
            {
                next = 0;
            }
            if(other->palette)
            {
                palette = new SDL_Palette_Wrapper(other->palette);
            }
        }
        ~SDL_PixelFormat_Wrapper()
        {
            SDL_PixelFormat_Wrapper* tmp;
            while(next != 0)
            {
                tmp = next;
                next = next->next;
                delete tmp;
            }
            if(palette)
            {
                delete palette;
            }
        }
        Uint32 format;
        SDL_Palette_Wrapper *palette;
        Uint8 BitsPerPixel;
        Uint8 BytesPerPixel;
        Uint8 padding[2];
        Uint32 Rmask;
        Uint32 Gmask;
        Uint32 Bmask;
        Uint32 Amask;
        Uint8 Rloss;
        Uint8 Gloss;
        Uint8 Bloss;
        Uint8 Aloss;
        Uint8 Rshift;
        Uint8 Gshift;
        Uint8 Bshift;
        Uint8 Ashift;
        int refcount;
        SDL_PixelFormat_Wrapper *next;
    };

    class SDL_Surface_Wrapper
    {
        public:
        SDL_Surface_Wrapper()
        {
            pixels = 0;
            map = 0;
        }
        ~SDL_Surface_Wrapper()
        {
            if(this)
            {
                if(pixels && flags == SDL_PREALLOC)
                {
                    free(pixels);
                    pixels = 0;
                }
                if(map)
                {
                    delete map;
                    map = 0;
                }
            }
        }
        Uint32 flags;               /**< Read-only */
        SDL_PixelFormat_Wrapper *format;    /**< Read-only */
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

    SDL_Surface* copySurface(SDL_Surface* surface)
    {
        SDL_Surface_Wrapper* other = (SDL_Surface_Wrapper*)surface;
        SDL_Surface_Wrapper* tx = new SDL_Surface_Wrapper();

        tx->clip_rect = other->clip_rect;
        tx->flags = 1;
        
        tx->format = new SDL_PixelFormat_Wrapper(other->format);
        tx->h = other->h;
        tx->w = other->w;
        tx->lock_data = other->lock_data;
        tx->locked = other->locked;
        tx->pitch = other->pitch;
        tx->refcount = other->refcount;
        tx->userdata = other->userdata;
        if(other->pixels)
        {
            tx->pixels = (Uint8*)calloc(tx->w * tx->h, 4);
            memcpy(tx->pixels, other->pixels, 4 * tx->w * tx->h);
        }
        else
        {
            tx->pixels = 0;
        }
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

