
class ContextMenu: public UIComponent
{
    MenuList* menu;
    SDL_Rect box;
    public:

    ContextMenu(int x, int y, int width, int hight, MenuList* menu, Window* window);

    bool update(Window* event) override;

    bool update(Window* window, SDL_Event& event) override;

    MenuList* getMenu()
    {
        return menu;
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

    SDL_Rect& getRect()
    {
        return box;
    }
};
