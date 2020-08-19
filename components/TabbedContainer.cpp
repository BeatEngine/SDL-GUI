

namespace LGUI
{


    bool ContainerTab::update(Window* window)
    {
        for(int i = 0; i < components.size(); i++)
        {
            components.at(i)->update(window);
        }
        return false;
    }


    bool ContainerTab::update(Window* window, SDL_Event& event)
    {
        bool update = false;
        for(int i = 0; i < components.size(); i++)
        {
            update = components.at(i)->update(window, event);
        }
        return false;
    }

    void ContainerTab::setEnabled(bool enabled)
    {
        for(int i = 0; i < components.size(); i++)
        {
            components.at(i)->setEnabled(enabled);
        }
        setProperties(isHidden(), enabled);
    }

    void ContainerTab::setHidden(bool hidden)
    {
        for(int i = 0; i < components.size(); i++)
        {
            components.at(i)->setHidden(hidden);
        }
        setProperties(hidden, isEnabled());
    }


    bool TabbedContainer::update(Window* window)
    {
        for(int i = 0; i < tabs.size(); i++)
        {
            tabs.at(i)->update(window);
        }
        return false;
    }


    bool TabbedContainer::update(Window* window, SDL_Event& event)
    {
        bool update = false;
        for(int i = 0; i < tabs.size(); i++)
        {
            update = tabs.at(i)->update(window, event);
            if(/*controls.at(i)->isSelected() &&*/ update)
            {
                tabs.at(i)->setSelected(true);
                for(int u = 0; u < tabs.size(); u++)
                {
                    if(u != i)
                    {
                        tabs.at(u)->setSelected(false);
                    }
                }
                break;
            }
        }
        return false;
    }

    void TabbedContainer::setEnabled(bool enabled)
    {
        for(int i = 0; i < tabs.size(); i++)
        {
            tabs.at(i)->setEnabled(enabled);
        }
        setProperties(isHidden(), enabled);
    }

    void TabbedContainer::setHidden(bool hidden)
    {
        for(int i = 0; i < tabs.size(); i++)
        {
            tabs.at(i)->setHidden(hidden);
        }
        setProperties(hidden, isEnabled());
    }


}



