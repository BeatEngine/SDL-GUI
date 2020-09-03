

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

    TabbedContainer::TabbedContainer(Window* window, ContainerTab* tabsNullTerminated[])
    {
        int i = 0;
        while (i < 1000)
        {
            if(tabsNullTerminated[i] == 0)
            {
                break;
            }
            tabs.push_back(tabsNullTerminated[i]);
            Button* tmp = new Button(0, 1, 60, 20, this->tabs.back()->getName(), RGBA(255, 255, 255, 255), RGBA(0, 0, 0, 255), window, 12);
            tmp->setPosition(62*buttons.size(), 1);
            buttons.push_back(tmp);
            buttons.back()->setParent(this);
            buttons.back()->setId(i);
            buttons.back()->setOnLeftClick(LGUI::TabbedContainer::_setTabbedContainerSelected);
            i++;
        }
        setDefaults();
        init();
    }


    bool TabbedContainer::update(Window* window)
    {
        tabs.at(selected)->update(window);
        for(int i = 0; i < buttons.size(); i++)
        {
            buttons.at(i)->update(window);
        }
        return false;
    }


    bool TabbedContainer::update(Window* window, SDL_Event& event)
    {
        tabs.at(selected)->update(window, event);
        for(int i = 0; i < buttons.size(); i++)
        {
            buttons.at(i)->update(window, event);
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

    void TabbedContainer::setPosition(int x, int y, Window* window)
    {
        SDL_Renderer* renderer = window->getRenderer();
        for(int i = 0; i < buttons.size(); i++)
        {
            buttons.at(i)->setPosition((buttons.at(0)->getRect().w + buttons.at(0)->getBorderSize())*i, y);
            if(i == 0)
            {
                buttons.at(i)->setPosition(0, y);
            }
        }
    }


}



