class InputBox;
class TableColumn: public UIComponent
{
    std::vector<InputBox> fields;
    std::string head = "";
    int x;
    int y;
    int width;
    RGBA background;
    RGBA border;
    int borderSize = 1;
    public:

    TableColumn()
    {

    }
    TableColumn(std::string& name, int x, int y, int width, RGBA colorBackground, RGBA colorBorder,Window* window, int borderSize = 1)
    {
        this->borderSize = borderSize;
        border = colorBorder;
        background = colorBackground;
        head = name;
        this->addRow(name, window, 14);
        this->x = x;
        this->y = y;
        this->width = width;
    }

    bool update(Window* window)override;

    bool update(Window* window, SDL_Event& event)override;

    void addRow(std::string& text, Window* window, int textSize);

    void addRow(Window* window, int textSize);

    int getWidth();

    int getHight()
    {
        int hi = 0;
        for(int i = 0; i < fields.size(); i++)
        {
            hi += fields.at(i).getRect().h;
        }
        return hi;
    }

    void setPosition(int px, int py)
    {
        x = px;
        y = py;
        for(int i = 0; i < fields.size(); i++)
        {
            fields.at(i).setPosition(x, y+20*i);
        }
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    std::string getText(int row);

    void setText(int row, std::string& text, SDL_Renderer* renderer, int textSize);

};

class Table: public UIComponent
{

    SDL_Rect box;
    RGBA fill;
    RGBA border;
    int borderSize = 1;
    int defaultTextSize = 12;
    UIComponent* optionalParent;
    Window* tableWindow = 0;

    std::vector<TableColumn> columns;

    void resize()
    {
        if(columns.size() > 0)
        {
            box.h = columns.at(0).getHight();
        }
        int wid = 0;
        for(int i = 0; i < columns.size(); i++)
        {
            wid += columns.at(i).getWidth();
        }
        box.w = wid;
    }

    public:

    Table(int x, int y, RGBA colorFill, RGBA colorBorder, Window* window, int textSize);

    bool update(Window* event) override;

    bool update(Window* window, SDL_Event& event) override;

    int getTextSize()
    {
        return defaultTextSize;
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
        int w = 0;
        for(int i = 0; i < columns.size(); i++)
        {
            columns.at(i).setPosition(box.x + w, box.y);
            w += columns.at(i).getWidth();
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

    void addColumn(std::string name)
    {
        columns.push_back(TableColumn(name, box.x+box.w, box.y, 50, fill, border, tableWindow, borderSize));
        resize();
        setPosition(box.x, box.y);
    }

    void addRows(int number)
    {
        while (number > 0)
        {
            for(int i = 0; i < columns.size(); i++)
            {
                columns.at(i).addRow(tableWindow, defaultTextSize);
            }
            number--;
        }
        resize();
    }

    SDL_Rect& getRect()
    {
        return box;
    }

    std::string getText(int row, int column)
    {
        if(column < columns.size())
        {
            return columns.at(column).getText(row);            
        }
    }

    void setText(int row, int column, std::string text, SDL_Renderer* renderer)
    {
        if(column < columns.size())
        {
            columns.at(column).setText(row, text, renderer, defaultTextSize);            
        }
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




