
class ScrollBox;

class ScrollBar: public UIComponent
{

    SDL_Rect box;
    RGBA fill;
    RGBA border;
    Button* button;

    int borderSize = 1;

    void* onLeftClick;
    void* onRightClick;

    UIComponent* optionalParent = 0;

    int lastX = -1;
    int lastY = -1;

    float lastDisplayQuoteV = 1;
    float lastDisplayQuoteH = 1;

    bool vertical = true;
    public:


    static void _scrollParentOnClick(void** params);

    void scrollOnClick(SDL_Event& event, LGUI::ScrollBox* scroll);

    void scrollParentOnClick(SDL_Event& event)
    {
        setLastCursor(event.button.x, event.button.y);
    }

    ScrollBar()
    {

    }

    ScrollBar(ScrollBar* other)
    {

    }

    ScrollBar(ScrollBar& other)
    {

    }

    ScrollBar(int x, int y, int width, int hight, RGBA colorFill, RGBA colorBorder, Window* window, bool vertical);

    bool update(Window* window) override;

    bool update(Window* window, SDL_Event& event) override;

    void setBackground(RGBA color)
    {
        fill = color;
    }

    void setBorder(RGBA color, int size = 1)
    {
        border = color;
        borderSize = size;
    }

    void setPosition(int x, int y, SDL_Renderer* renderer)
    {
        box.x = x;
        box.y = y;
    }

    void setLastCursor(int x, int y)
    {
        lastX = x;
        lastY = y;
    }

    int getLastX()
    {
        return lastX;
    }

    int getLastY()
    {
        return lastY;
    }

    unsigned int getBorderSize()
    {
        return borderSize;
    }

    SDL_Rect& getRect()
    {
        return box;
    }

    void setHorizontalDisplayQuote(float quote, float scrollX)
    {
        if(!vertical)
        {
            lastDisplayQuoteH = quote;
            button->setSize((box.w-2)*quote, button->getRect().h);
            button->setPosition(box.x + (1-scrollX)*(box.w-button->getRect().w), button->getRect().y);
        }
    }

    void setVerticalDisplayQuote(float quote, float scrollY)
    {
        if(vertical)
        {
            lastDisplayQuoteV = quote;
            button->setSize(button->getRect().w, (box.h-2)*quote);
            button->setPosition(button->getRect().x, box.y + scrollY*(box.h-button->getRect().h));
        }
    }

    float getDisplayQuote()
    {
        if(vertical)
        {
            return lastDisplayQuoteV;
        }
        return lastDisplayQuoteH;
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

    

};


