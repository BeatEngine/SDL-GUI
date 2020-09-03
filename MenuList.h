
class MenuList;

class MenuEntriy: public UIComponent
{

    SDL_Rect box;
    RGBA textColor;
    UIComponent* optionalParent;
    Text text;

    void* onLeftClick;
    void* onRightClick;

    MenuList* subMenu = NULL;

    public:

    MenuEntriy()
    {
        optionalParent = 0;
        onLeftClick = 0;
        onRightClick = 0;
    }

    ~MenuEntriy();

    MenuEntriy(int x, int y, int width, int hight, std::string text, Window* window, int textSize, MenuList* setSubMenu);

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

    void setPosition(int x, int y)
    {
        box.x = x;
        box.y = y;
        text.setPositionCenter(x + box.w/2, y + box.h/2);
        text.setPosition(x, text.getPosition().y);
    }

    void setSize(int width, int hight)
    {
        box.w = width;
        box.h = hight;
        text.setPositionCenter(box.x + box.w/2, box.y + box.h/2);
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


class MenuList: public UIComponent
{

    SDL_Rect box;
    SDL_Rect selectBox;
    RGBA fill;
    RGBA selectColor;
    RGBA border;
    RGBA textColor;
    int initialTextSize = 12;
    int borderSize = 1;
    bool mouseInBox = false;
    std::vector<UIComponent*> overlappedComponents;

    UIComponent* optionalParent;

    std::vector<MenuEntriy*> entries;

    public:

    MenuList(int x, int y, int width, int hight, RGBA colorFill, RGBA colorSelect, RGBA colorBorder, Window* window, int textSize);

    ~MenuList()
    {
        while (entries.size() > 0)
        {
            delete entries.back();
            entries.pop_back();
        }
        
    }

    bool update(Window* event) override;

    bool update(Window* window, SDL_Event& event) override;

    void addEntrie(std::string text, Window* window, void (*onClickEvent)(void** parameters), MenuList* subMenu = 0)
    {
        entries.push_back(new MenuEntriy(box.x+15, box.y + entries.size()*20, 70, 20, text, window, initialTextSize, subMenu));
        entries.back()->setOnLeftClick(onClickEvent);
        setSize(70, entries.size()*20);
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
        for(int i = 0; i < entries.size(); i++)
        {
            entries.at(i)->setPosition(x+15, y + i*20);
        }
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

    void setEnabled(bool enabled)
    {
        if(overlappedComponents.size() > 0 && !enabled)
        {
            for(int i = 0; i < overlappedComponents.size(); i++)
            {
                overlappedComponents.at(i)->setEnabled(true);
            }
            overlappedComponents.clear();
        }
        this->setProperties(isHidden(), enabled);
    }

    SDL_Rect& getRect()
    {
        return box;
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

