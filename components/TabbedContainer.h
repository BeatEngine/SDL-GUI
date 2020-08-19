
namespace LGUI
{

    class ContainerTab: public UIComponent
    {
        std::vector<UIComponent*> components;
        bool selected = false;
        public:
        
        ContainerTab()
        {

        }

        ContainerTab(int components , UIComponent*...)
        {
            va_list argumente;
            int i;
            double summe = 0;

            va_start(argumente, components);
            for (i = 0; i < components; i++)
            {
                this->components.push_back((UIComponent*)va_arg(argumente, UIComponent*));
            }
            va_end(argumente);
        }

        ContainerTab(UIComponent* componentsNullTerminated[])
        {
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
        public:

        TabbedContainer()
        {

        }

        TabbedContainer(int tabs , ContainerTab*...)
        {
            va_list argumente;
            int i;
            double summe = 0;

            va_start(argumente, tabs);
            for (i = 0; i < tabs; i++)
            {
                this->tabs.push_back(va_arg(argumente, ContainerTab*));
            }
            va_end(argumente);
        }

        TabbedContainer(ContainerTab* tabsNullTerminated[])
        {
            int i = 0;
            while (i < 1000)
            {
                if(tabsNullTerminated[i] == 0)
                {
                    break;
                }
                tabs.push_back(tabsNullTerminated[i]);
                i++;
            }
        }

        ~TabbedContainer()
        {
            while(tabs.size() > 0)
            {
                delete tabs.back();
                tabs.pop_back();
            }
        }

        bool update(Window* window) override;

        bool update(Window* window, SDL_Event& event) override;

        void setEnabled(bool enabled);

        void setHidden(bool hidden);

    };



}

