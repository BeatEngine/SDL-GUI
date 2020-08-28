
class ContainerTab: public UIComponent
{
    std::vector<UIComponent*> components;
    bool selected = false;
    std::string name;
    public:
    
    ContainerTab()
    {
        name = "";
    }

    ContainerTab(std::string name)
    {
        this->name = name;
    }

    std::string& getName()
    {
        return name;
    }

    ContainerTab(std::string tabName, int components , UIComponent*...)
    {
        va_list argumente;
        int i;
        double summe = 0;
        name = tabName;
        va_start(argumente, components);
        for (i = 0; i < components; i++)
        {
            this->components.push_back((UIComponent*)va_arg(argumente, UIComponent*));
        }
        va_end(argumente);
    }

    ContainerTab(std::string tabName, UIComponent* componentsNullTerminated[])
    {
        name = tabName;
        int i = 0;
        while (i < 100000)
        {
            if(componentsNullTerminated[i] == 0)
            {
                break;
            }
            components.push_back(componentsNullTerminated[i]);
            i++;
        }
    }

    ~ContainerTab()
    {
        while(components.size() > 0)
        {
            delete components.back();
            components.pop_back();
        }
    }

    bool isSelected()
    {
        return selected;
    }

    void setSelected(bool selected)
    {
        this->selected = selected;
    }

    bool update(Window* window) override;

    bool update(Window* window, SDL_Event& event) override;

    void setEnabled(bool enabled);

    void setHidden(bool hidden);

};



class TabbedContainer: public UIComponent
{
    std::vector<ContainerTab*> tabs;
    std::vector<Button*> buttons;
    unsigned int selected = 0;

    RGBA selectedButtonBackground;
    RGBA buttonBackground;

    void init()
    {
        for(int i = 0; i < tabs.size(); i++)
        {
            if(i != selected)
            {
                tabs.at(i)->setHidden(true);
                tabs.at(i)->setEnabled(false);
                buttons.at(i)->setBackground(buttonBackground);
                buttons.at(i)->setBorder(RGBA(100,100,100,255), 2);
            }
            else
            {
                tabs.at(i)->setEnabled(true);
                tabs.at(i)->setHidden(false);
                buttons.at(i)->setBackground(selectedButtonBackground);
                buttons.at(i)->setBorder(RGBA(0,0,0,255), 2);
            }
        }
    }

    void setDefaults()
    {
        selectedButtonBackground.r = 200;
        selectedButtonBackground.g = 200;
        selectedButtonBackground.b = 200;
        selectedButtonBackground.a = 255;
        buttonBackground.r = 150;
        buttonBackground.g = 150;
        buttonBackground.b = 150;
        buttonBackground.a = 255;
    }

    public:

    static void _setTabbedContainerSelected(void** params)
    {
        Button* button = (LGUI::Button*)params[1];
        Window* window = (LGUI::Window*)params[0];
        TabbedContainer* select = (TabbedContainer*)button->getParentWhenSet();
        select->select(button->getId());
    }

    TabbedContainer()
    {
        setDefaults();
    }

    TabbedContainer(Window* window, int tabs , ContainerTab*...);

    TabbedContainer(Window* window, ContainerTab* tabsNullTerminated[]);

    ~TabbedContainer()
    {
        while(tabs.size() > 0)
        {
            delete tabs.back();
            tabs.pop_back();
            buttons.pop_back();
        }
    }

    void setPosition(int x, int y, Window* window);

    void select(unsigned int pos)
    {
        if(selected != pos && pos < tabs.size())
        {
            tabs.at(selected)->setEnabled(false);
            tabs.at(selected)->setHidden(true);
            tabs.at(selected)->setSelected(false);
            buttons.at(selected)->setBackground(buttonBackground);
            buttons.at(selected)->setBorder(RGBA(100,100,100,255), 2);
            selected = pos;
            buttons.at(selected)->setBackground(selectedButtonBackground);
            buttons.at(selected)->setBorder(RGBA(0,0,0,255), 2);
            tabs.at(selected)->setSelected(true);
            tabs.at(selected)->setEnabled(true);
            tabs.at(selected)->setHidden(false);
        }
    }

    void setTabButtonBackround(RGBA color)
    {
        buttonBackground = color;
        for(int i = 0; i < buttons.size(); i++)
        {
            if(i != selected)
            {
                buttons.at(i)->setBackground(buttonBackground);
            }  
        }
    }

    void setTabButtonSelectedBackground(RGBA color)
    {
        selectedButtonBackground = color;
        buttons.at(selected)->setBackground(color);
    }

    bool update(Window* window) override;

    bool update(Window* window, SDL_Event& event) override;

    void setEnabled(bool enabled);

    void setHidden(bool hidden);

};
