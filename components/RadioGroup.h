

class RadioGroup: public UIComponent
{
    public:
    std::vector<RadioBox*> controls;

    RadioGroup()
    {

    }

    RadioGroup(int radioboxes , RadioBox*...)
    {
        va_list argumente;
        int i;
        double summe = 0;

        va_start(argumente, radioboxes);
        for (i = 0; i < radioboxes; i++)
        {
            controls.push_back(va_arg(argumente, RadioBox*));
        }
        va_end(argumente);
    }

    RadioGroup(RadioBox* radiosNullTerminated[])
    {
        int i = 0;
        while (i < 1000)
        {
            if(radiosNullTerminated[i] == 0)
            {
                break;
            }
            controls.push_back(radiosNullTerminated[i]);
            i++;
        }
    }

    ~RadioGroup()
    {
        while(controls.size() > 0)
        {
            delete controls.back();
            controls.pop_back();
        }
    }


    std::vector<RadioBox*>& getControlls()
    {
        return controls;
    }
    

    void addRadioBox(RadioBox* box)
    {
        controls.push_back(box);
    }

    bool update(Window* window) override;

    bool update(Window* window, SDL_Event& event) override;

    void setEnabled(bool enabled);

    void setHidden(bool hidden);




};



