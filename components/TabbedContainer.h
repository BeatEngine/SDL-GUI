
namespace LGUI
{

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

        void init()
        {
            for(int i = 0; i < tabs.size(); i++)
            {
                if(i != selected)
                {
                    tabs.at(i)->setHidden(true);
                    tabs.at(i)->setEnabled(false);
                }
                else
                {
                    tabs.at(i)->setEnabled(true);
                    tabs.at(i)->setHidden(false);
                }
            }
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
                selected = pos;
                tabs.at(selected)->setSelected(true);
                tabs.at(selected)->setEnabled(true);
                tabs.at(selected)->setHidden(false);
            }
        }

        bool update(Window* window) override;

        bool update(Window* window, SDL_Event& event) override;

        void setEnabled(bool enabled);

        void setHidden(bool hidden);

    };



}

