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

