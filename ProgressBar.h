

class ProgressBar: public UIComponent
{

    SDL_Rect box;
    std::string lableText = "";
    Text text;
    bool showText = true;
    RGBA fill;
    RGBA border;
    RGBA background;
    float cornerRadius = 5;

    float progress = 0.0f;

    int borderSize = 1;
    UIComponent* optionalParent;

    static int numLength(float x)
    {
        if(x < 1 && x > 0)
        {
            return 1;
        }
        int l = 0;
        while (x >= 1)
        {
            l++;
            x /= 10;
        }
        return l;
    }
    public:

    ProgressBar(int x, int y, int width, int hight, std::string text, RGBA colorFill, RGBA colorBackground, RGBA colorBorder, Window* window,bool showNumericalProgress,  int textSize);

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
        background = color;
    }

    void setFill(RGBA color)
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

    float getProgress()
    {
        return progress;
    }

    void setBoxCornerRadius(float radius)
    {
        cornerRadius = radius;
    }

    

    void setProgress(float prog, SDL_Renderer*  renderer)
    {
        progress = prog;
        std::string resTxt = lableText + std::to_string((float)((int)(progress*10000)/100)).substr(0, numLength((float)((int)(progress*10000)/100))+3);
        text.setText(resTxt, renderer);
    }

    SDL_Rect& getRect()
    {
        return box;
    }

    std::string getText()
    {
        return this->text.getText();
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

