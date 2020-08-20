
namespace LGUI
{


    class ScrollBox: public UIComponent
    {
        SDL_Rect box;
        RGBA fill;
        RGBA border;

        ScrollBar* verticalBar;
        ScrollBar* horizontalBar;

        int borderSize = 1;

        bool selected = false;

        void* onLeftClick;
        void* onRightClick;

        float scrollX = 0;
        float scrollY = 0;

        int lastX = 0;
        int lastY = 0;

        std::vector<UIComponent*> components;
        std::vector<SDL_Rect> relativePositions;


        void updateRelativePositions()
        {
            for(int i = 0; i < components.size(); i++)
            {
                components.at(i)->setPosition(box.x + relativePositions.at(i).x - box.w * scrollX, box.y + relativePositions.at(i).y - box.h * scrollY);
            }
            int maxX = 1;
            int maxY = 1;
            for(int i = 0; i < relativePositions.size(); i++)
            {
                if(relativePositions.at(i).x + relativePositions.at(i).w > maxX)
                {
                    maxX = relativePositions.at(i).x + relativePositions.at(i).w;
                }
                if(relativePositions.at(i).y + relativePositions.at(i).h > maxY)
                {
                    maxY = relativePositions.at(i).y + relativePositions.at(i).h;
                }
            }
            verticalBar->setVerticalDisplayQuote(box.h / (float)maxY);
            horizontalBar->setVerticalDisplayQuote(box.w / (float)maxX);
        }

        public:

        ScrollBox(ScrollBox* other)
        {

        }

        ScrollBox(ScrollBox& other)
        {

        }

        ~ScrollBox()
        {
            delete verticalBar;
            delete horizontalBar;
            relativePositions.clear();
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
            if(sx < 0)
            {
                sx = 0;
            }
            if(sx > 1)
            {
                sx = 1;
            }
            if(sy < 0)
            {
                sy = 0;
            }
            if(sy > 1)
            {
                sy = 1;
            }
            scrollX = sx;
            scrollY = sy;
            updateRelativePositions();
        }

        float getScrollX()
        {
            return scrollX;
        }


        float getScrollY()
        {
            return scrollY;
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


