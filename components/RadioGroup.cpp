

namespace LGUI
{


    bool RadioGroup::update(Window* window)
    {
        for(int i = 0; i < controls.size(); i++)
        {
            controls.at(i)->update(window);
            /*if(controls.at(i)->isSelected())
            {
                for(int o = 0; o < controls.size(); o++)
                {
                    if(i != 0)
                    {
                        controls.at(o)->setSelected(false);
                        if(o > i)
                        {
                            controls.at(o)->update(window);
                        }
                    }
                }
                break;
            }*/
        }
        return false;
    }


    bool RadioGroup::update(Window* window, SDL_Event& event)
    {
        bool update = false;
        for(int i = 0; i < controls.size(); i++)
        {
            update = controls.at(i)->update(window, event);
            if(/*controls.at(i)->isSelected() &&*/ update)
            {
                controls.at(i)->setSelected(true);
                for(int u = 0; u < controls.size(); u++)
                {
                    if(u != i)
                    {
                        controls.at(u)->setSelected(false);
                    }
                }
                break;
            }
        }
        return false;
    }

    void RadioGroup::setEnabled(bool enabled)
    {
        for(int i = 0; i < controls.size(); i++)
        {
            controls.at(i)->setEnabled(enabled);
        }
        setProperties(isHidden(), enabled);
    }

    void RadioGroup::setHidden(bool hidden)
    {
        for(int i = 0; i < controls.size(); i++)
        {
            controls.at(i)->setHidden(hidden);
        }
        setProperties(hidden, isEnabled());
    }


}



