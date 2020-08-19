namespace LGUI
{



class InputBox: public UIComponent
    {

        SDL_Rect box;
        Text text;
        RGBA fill;
        RGBA border;

        int borderSize = 1;

        void* onLeftClick;
        void* onRightClick;

        bool selected = false;

        bool shift = false;
        bool lockShift = false;

        bool lineBreak = false;

        std::string textPart = "";

        void append(char* txt, SDL_Renderer* renderer)
        {
            std::string tex = getText() + std::string(txt);
            setText(tex, renderer);
        }

        void pop(SDL_Renderer* renderer)
        {
            std::string tex = getText();
            if(tex.length() > 0)
            {
                tex.pop_back();
            }
            setText(tex, renderer);
        }

        void clear(SDL_Renderer* renderer)
        {
            textPart = "";
            std::string txt("");
            setText(txt, renderer);
        }

        public:

        bool isSelected()
        {
            return selected;
        }

        void enableLineBreak(bool allowed)
        {
            lineBreak = allowed;
        }

        InputBox(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBorder, Window* window, int textSize);

        bool update(Window* event) override;

        bool update(Window* window, SDL_Event& event) override;

        void setText(std::string& text, SDL_Renderer* renderer, int fontSize = -1)
        {
            
            while(text.length() > 0 && box.w-getTextSize() < text.length()*getTextSize()/2.150)
            {
                char tmp[2] = {0};
                tmp[0] = text.at(0);
                textPart.append(tmp, 1);
                text.erase(text.begin());
            }
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
            return textPart + this->text.getText();
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

