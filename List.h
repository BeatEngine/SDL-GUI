
class List: public UIComponent
{
    SDL_Rect box;
    RGBA fill;
    RGBA border;
    int borderSize = 1;
    void* onLeftClick;
    void* onRightClick;
    UIComponent* optionalParent;


    std::vector<UIComponent*> elements;


    void setElementsPositions()
    {

        int midX = box.x + 5;
        int midY = box.h/(1+elements.size());

        for(int i = 0; i < elements.size(); i++)
        {
            elements.at(i)->setPosition(midX, midY*(i+1) + box.y);
        }


    }

    public:

    List(List* other)
    {

    }

    List(List& other)
    {

    }

    List(int x, int y, int width, int hight, RGBA colorFill, RGBA colorBorder, Window* window, UIComponent** elementsListNullTerminated);

    void push(UIComponent* element)
    {
        elements.push_back(element);
        setElementsPositions();
    }

    void pop()
    {
        elements.pop_back();
        setElementsPositions();
    }

    void remove(unsigned int position)
    {
        elements.erase(elements.begin() + position);
        setElementsPositions();
    }

    SDL_Rect& getPosition() override
    {
        return box;
    }

    void setPosition(int x, int y) override
    {
        box.x = x;
        box.y = y;
        setElementsPositions();
    }

    UIComponent* at(unsigned int position)
    {
        return elements.at(position);
    }

    bool update(Window* event) override;

    bool update(Window* window, SDL_Event& event) override;

    bool hasPosition() override
    {
        return true;
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

    void setPosition(int x, int y, SDL_Renderer* renderer)
    {
        box.x = x;
        box.y = y;
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

};

