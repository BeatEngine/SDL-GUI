

namespace LGUI
{
    class RGBA
    {
        public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        RGBA()
        {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
        }
        RGBA(uint8_t red,uint8_t green,uint8_t blue,uint8_t alpha)
        {
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }

        void operator = (RGBA& other)
        {
            r = other.r;
            g = other.g;
            b = other.g;
            a = other.a;
        }
    };

class Window;

    class UIComponent
    {
        unsigned int id;
        bool hidden = false;
        bool enabled = true;
        public:

        virtual bool update(Window* window)
        {
            return false;
        }

        virtual bool update(Window* window, SDL_Event& event)
        {
            return false;
        }

        virtual void setHidden(bool hidden)
        {
            this->hidden = hidden;
        }

        virtual void setEnabled(bool enabled)
        {
            this->enabled = enabled;
        }

        void setProperties(bool hidden, bool enabled)
        {
            this->hidden = hidden;
            this->enabled = enabled;
        }

        bool isHidden()
        {
            return hidden;
        }

        bool isEnabled()
        {
            return enabled;
        }

        void setId(unsigned int id)
        {
            this->id = id;
        }

        unsigned int getId()
        {
            return id;
        }

    };
}


