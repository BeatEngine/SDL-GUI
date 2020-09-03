

class Button: public UIComponent
{

    SDL_Rect box;
    Text text;
    RGBA fill;
    RGBA border;

    int borderSize = 1;

    void* onLeftClick;
    void* onRightClick;
    UIComponent* optionalParent;
    public:

    Button(Button* other)
    {

    }

    Button(Button& other)
    {

    }

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

    void setBackground(RGBA color)
    {
        fill = color;
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
        text.setPositionCenter(x + box.w/2, y + box.h/2);
    }

    void setSize(int width, int hight)
    {
        box.w = width;
        box.h = hight;
        text.setPositionCenter(box.x + box.w/2, box.y + box.h/2);
    }

    unsigned int getBorderSize()
    {
        return borderSize;
    }

    SDL_Rect& getRect()
    {
        return box;
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




