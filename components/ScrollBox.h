
namespace LGUI
{


    class ScrollBox: public UIComponent
    {
        SDL_Rect box;
        RGBA fill;
        RGBA border;

        int borderSize = 1;

        bool selected = false;

        void* onLeftClick;
        void* onRightClick;

        float scrollX = 0;
        float scrollY = 0;

        std::vector<UIComponent*> components;
        std::vector<SDL_Rect> relativePositions;


        void updateRelativePositions()
        {
            for(int i = 0; i < components.size(); i++)
            {
                components.at(i)->setPosition(box.x + relativePositions.at(i).x - box.w * scrollX, box.y + relativePositions.at(i).y - box.h * scrollY);
            }
        }

        public:

        ScrollBox(ScrollBox* other)
        {

        }

        ScrollBox(ScrollBox& other)
        {

        }

        ScrollBox(int x, int y, int width, int hight, RGBA colorFill, RGBA colorBorder, Window* window, UIComponent** componentsNullTerminated);

        bool update(Window* event) override;

        bool update(Window* window, SDL_Event& event) override;

        void push(UIComponent* element)
        {
            components.push_back(element);
            updateRelativePositions();
        }

        void pop()
        {
            components.pop_back();
            updateRelativePositions();
        }

        void remove(unsigned int position)
        {
            components.erase(components.begin() + position);
            updateRelativePositions();
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

        SDL_Rect& getPosition() override
        {
            return box;
        }

        bool hasPosition() override
        {
            return true;
        }

        void setScroll(float sx, float sy)
        {
            scrollX = sx;
            scrollY = sy;
            updateRelativePositions();
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

    };

}


