
class SortStruct
{
    public:
    SortStruct(std::string dat, int indx)
    {
        data = dat;
        oldIndex = indx;
    }
    std::string data;
    int oldIndex;

    static bool isNumber(std::string& str)
    {
        if(str.size() <= 0)
        {
            return false;
        }
        for(int i = 0; i < str.length(); i++)
        {
            if(str[i] != 32 && (str[i] < 48 || str[i] > 57) && str[i] != '.')
            {
                return false;
            }
        }
        return true;
    }

    static bool compare(SortStruct& a, SortStruct& b)
    {
        if(isNumber(a.data) && isNumber(b.data))
        {
            //printf("%d\n", (int)((strtof(a.data.c_str(),0)-strtof(b.data.c_str(),0))));
            return strtof(a.data.c_str(),0) < strtof(b.data.c_str(),0);//(int)((strtof(a.data.c_str(),0)-strtof(b.data.c_str(),0)));
        }
        return a.data.compare(b.data) < 0;
    }

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
    bool sortOnHeadClick = false;

    std::vector<InputBox> cells;
    int rows = 0;
    int columns = 0;

    void resize()
    {
        int mw = 0;
        int mh = 0;
        int w = 0;
        int h = 0;
        int c;
        for(int r = 0; r <= rows; r++)
        {
            w = 0;
            h = 0;
            for(c = 0; c < columns; c++)
            {
                cells[columns*r+c].setPosition(box.x + w, box.y + mh);
                if(cells[columns*r+c].getRect().h > h)
                {
                    h = cells[columns*r+c].getRect().h;
                }
                w += cells[columns*r+c].getRect().w;
            }
            if(w > mw)
            {
                mw = w;
            }
            mh += h;
        }
        box.w = mw;
        box.h = mh;
        mw = 0;
        for(c = 0; c < columns; c++)
        {
            w = 0;
            for(int r = 0; r <= rows; r++)
            {
                if(cells[columns*r+c].getRect().w > w)
                {
                    w = cells[columns*r+c].getRect().w;
                }
            }
            for(int r = 0; r <= rows; r++)
            {
                if(cells[columns*r+c].getRect().w < w)
                {
                    cells[columns*r+c].setPosition(box.x + mw + (w-cells[columns*r+c].getRect().w)/2,cells[columns*r+c].getRect().y);
                }
                else
                {
                    cells[columns*r+c].setPosition(box.x + mw,cells[columns*r+c].getRect().y);
                }
            }
            mw += w;
        }



    }

    public:

    Table(int x, int y, RGBA colorFill, RGBA colorBorder, Window* window, int textSize);

    bool update(Window* event) override;

    bool update(Window* window, SDL_Event& event) override;

    void refresh()
    {
        int c = 0;
        for(int i = 0; i < countRows(); i++)
        {
            for(c = 0; c < countColumns(); c++)
            {
                setText(i, c, getText(i, c));
            }
        }
    }

    int getTextSize()
    {
        return defaultTextSize;
    }

    void sortTable(int column);

    void setSortableOnHeadClick(bool sortable)
    {
        sortOnHeadClick = sortable;
        if(sortOnHeadClick)
        {
            for(int c = 0; c < columns; c++)
            {
                cells[c].setEnabled(false);
            }
        }
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
        resize();
        /*for(int i = 0; i < cells.size(); i++)
        {
            cells.at(i).setPosition(box.x + (i % rows)*50, box.y + (i / rows)*20);
        }*/
    }

    int countRows()
    {
        return rows+1;
    }

    int countColumns()
    {
        return columns;
    }

    void setSize(int width, int hight)
    {
        //box.w = width;
        //box.h = hight;
    }

    unsigned int getBorderSize()
    {
        return borderSize;
    }

    void addColumn(std::string name, int textSize = -1)
    {
        if(textSize == -1)
        {
            textSize = defaultTextSize;
        }
        int p = cells.size();
        while (p >= columns)
        {
            if(p == 0)
            {
                if(textSize <= 12)
                {
                    cells.insert(cells.begin()+p, InputBox(0, 0, 0, 20, name, fill, border, tableWindow, textSize));
                }
                else
                {
                    cells.insert(cells.begin()+p, InputBox(0, 0, 0, 0, name, fill, border, tableWindow, textSize));
                }
                cells[p].setBorder(border, 0);
            }
            else if(p % columns == 0)
            {
                if(p <= columns)
                {
                    if(textSize <= 12)
                    {
                        cells.insert(cells.begin()+p, InputBox(0, 0, 0, 20, name, fill, border, tableWindow, textSize));
                    }
                    else
                    {
                        cells.insert(cells.begin()+p, InputBox(0, 0, 0, 0, name, fill, border, tableWindow, textSize));
                    }
                    cells[p].setBorder(border, 0);
                }
                else
                {
                    cells.insert(cells.begin()+p, InputBox(0, 0, 60, 0, "", fill, border, tableWindow, textSize));
                    cells[p].setBorder(border, 0);
                }
            }
            p--;
        }
        columns++;
        resize();
    }

    void addRow()
    {
        for(int i = 0; i < columns; i++)
        {
            cells.push_back(InputBox(0, 0, 60, 20, "", fill, border, tableWindow, defaultTextSize));
        }
        rows++;
        resize();
    }

    void addRow(std::vector<std::string>& row)
    {
        for(int i = 0; i < columns; i++)
        {
            if(i < row.size())
            {
                cells.push_back(InputBox(0, 0, 0, 20, row[i], fill, border, tableWindow, defaultTextSize));
            }
            else
            {
                cells.push_back(InputBox(0, 0, 60, 20, "", fill, border, tableWindow, defaultTextSize));
            }
        }
        rows++;
        resize();
    }
    void addRow(std::vector<LGUI::InputBox>& row)
    {
        for(int i = 0; i < columns; i++)
        {
            if(i < row.size())
            {
                cells.push_back(InputBox(0, 0, 0, 20, row[i].getText(), fill, border, tableWindow, defaultTextSize));
            }
            else
            {
                cells.push_back(InputBox(0, 0, 60, 20, "", fill, border, tableWindow, defaultTextSize));
            }
        }
        rows++;
        resize();
    }
    void addRow(std::vector<LGUI::InputBox*>& row)
    {
        for(int i = 0; i < columns; i++)
        {
            if(i < row.size())
            {
                if(row[i])
                {
                    cells.push_back(InputBox(0, 0, 60, 20, row[i]->getText(), fill, border, tableWindow, defaultTextSize));
                }
                else
                {
                    cells.push_back(InputBox(0, 0, 60, 20, "", fill, border, tableWindow, defaultTextSize));
                }
            }
            else
            {
                cells.push_back(InputBox(0, 0, 60, 20, "", fill, border, tableWindow, defaultTextSize));
            }
        }
        rows++;
        resize();
    }
    void addRow(char** row, int entries)
    {
        for(int i = 0; i < columns; i++)
        {
            if(i < entries)
            {
                if(row[i])
                {
                    cells.push_back(InputBox(0, 0, 60, 20, std::string(row[i]), fill, border, tableWindow, defaultTextSize));
                    cells.back().setBorder(border, 0);
                }
                else
                {
                    cells.push_back(InputBox(0, 0, 60, 20, "", fill, border, tableWindow, defaultTextSize));
                    cells.back().setBorder(border, 0);
                }
            }
            else
            {
                cells.push_back(InputBox(0, 0, 60, 20, "", fill, border, tableWindow, defaultTextSize));
                cells.back().setBorder(border, 0);
            }
        }
        rows++;
        resize();
    }

    SDL_Rect& getRect()
    {
        return box;
    }

    std::string getText(int row, int column)
    {
        if(row*columns+column < cells.size())
        {
            return cells[row*columns+column].getText();            
        }
        return "Error: Out of range";
    }

    void setText(int row, int column, std::string text);

    UIComponent* getParentWhenSet()
    {
        return optionalParent;
    }

    void setParent(UIComponent* parent)
    {
        optionalParent = parent;
    }

};




