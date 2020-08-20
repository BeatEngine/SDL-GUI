
namespace LGUI
{


    class ScrollBar: public UIComponent
    {

        SDL_Rect box;
        RGBA fill;
        RGBA border;
        Button* button;

        int borderSize = 1;

        void* onLeftClick;
        void* onRightClick;

        UIComponent* optionalParent;

        bool vertical = true;
        public:


        static void _scrollParentOnClick(void** params)
        {
            LGUI::ScrollBar* scrollBar = (LGUI::ScrollBar*)params[1];
            LGUI::Window* window = (LGUI::Window*)params[0];

            SDL_Event* event = (SDL_Event*)params[2];

            //LGUI::ScrollBox* scroll = (LGUI::ScrollBox*)(scrollBar->getParentWhenSet());
        /*
            if(event->motion.y < 0 && scroll->getScrollY() < 1)
            {
                scroll->setScroll(scroll->getScrollX(), scroll->getScrollY() + (-event->motion.y*3)/100.0f);
            }
            else if(scroll->getScrollY() > 0)
            {
                scroll->setScroll(scroll->getScrollX(), scroll->getScrollY() - event->motion.y*3/100.0f);
            }
            if(event->motion.x > 0 && scroll->getScrollX() < 1)
            {
                scroll->setScroll(scroll->getScrollX() + event->motion.x*3/100.0f, scroll->getScrollY());
            }
            else if(scroll->getScrollX() > 0)
            {
                scroll->setScroll(scroll->getScrollX() + event->motion.x*3/100.0f, scroll->getScrollY());
            }*/

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

        unsigned int getBorderSize()
        {
            return borderSize;
        }

        SDL_Rect& getRect()
        {
            return box;
        }

        void setHorizontalDisplayQuote(float quote)
        {
            if(!vertical)
            {
                button->setSize((box.w-2)*quote, button->getRect().h);
            }
        }

        void setVerticalDisplayQuote(float quote)
        {
            if(vertical)
            {
                button->setSize(button->getRect().w, (box.h-2)*quote);
            }
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

}


