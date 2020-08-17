
namespace LGUI
{


class RadioBox: public UIComponent
    {

        Text text;
        RGBA fill;
        RGBA border;

        int borderSize = 1;
        int radius = 2;
        int x = 0;
        int y = 0;

        void* onLeftClick;
        void* onRightClick;

        bool selected = false;

        public:

        RadioBox(int x, int y, int radius, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize);

        bool update(Window* event) override;

        bool update(Window* window, SDL_Event& event) override;

        bool isSelected()
        {
            return selected;
        }

        void setSelected(bool selected)
        {
            this->selected = selected;
        }

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

        void setBorder(RGBA color, int size = 1)
        {
            border = color;
            borderSize = size;
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

    };

}


