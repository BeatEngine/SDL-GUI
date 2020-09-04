

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

    void operator = (const RGBA& other)
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
    bool hidden = false;
    bool enabled = true;
    int layer = 1;

    SDL_Rect renderFrameDrawBorder = {0, 0, 9999999, 9999999};

    public:

    static inline bool compareLayer(UIComponent* a, UIComponent* b)
    {
        return a->getLayer() < b->getLayer();
    }

    virtual bool update(Window* window)
    {
        return false;
    }

    virtual bool update(Window* window, SDL_Event& event)
    {
        return false;
    }

    virtual void setHidden(bool hidden)
    {
        this->hidden = hidden;
    }

    virtual void setEnabled(bool enabled)
    {
        this->enabled = enabled;
    }

    void setProperties(bool hidden, bool enabled)
    {
        this->hidden = hidden;
        this->enabled = enabled;
    }

    bool isHidden()
    {
        return hidden;
    }

    bool isEnabled()
    {
        return enabled;
    }

    void setId(unsigned int id)
    {
        this->id = id;
    }

    unsigned int getId()
    {
        return id;
    }

    virtual void setPosition(int x, int y)
    {
        return;
    }

    virtual bool hasPosition()
    {
        return false;
    }

    virtual SDL_Rect& getPosition()
    {
        return *(new SDL_Rect);
    }

    bool rectIsInBorders(SDL_Rect& rect)
    {
        if(rect.x >= renderFrameDrawBorder.x && rect.x + rect.w < renderFrameDrawBorder.x + renderFrameDrawBorder.w)
        {
            if(rect.y >= renderFrameDrawBorder.y && rect.y + rect.h < renderFrameDrawBorder.y + renderFrameDrawBorder.h)
            {
                return true;
            }
        }
        return false;
    }

    int getLayer()
    {
        return layer;
    }

    void setLayer(int layer)
    {
        this->layer = layer;
    }

    SDL_Rect& getDrawBorderRect()
    {
        return renderFrameDrawBorder;
    }

    void setDrawBordersRect(SDL_Rect& maximalRect)
    {
        renderFrameDrawBorder = maximalRect;
    }

    SDL_Rect cropToDrawBorders(SDL_Rect& rect)
    {
        SDL_Rect cropped = rect;
        if(cropped.x < renderFrameDrawBorder.x)
        {
            cropped.x = renderFrameDrawBorder.x;
        }
        if(cropped.y < renderFrameDrawBorder.y)
        {
            cropped.y = renderFrameDrawBorder.y;
        }
        if(cropped.w > renderFrameDrawBorder.w)
        {
            cropped.w = renderFrameDrawBorder.w;
        }
        if(cropped.h > renderFrameDrawBorder.h)
        {
            cropped.h = renderFrameDrawBorder.h;
        }
        return cropped;
    }

};



