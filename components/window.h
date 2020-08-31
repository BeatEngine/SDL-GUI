#include <time.h>
#include <algorithm>
namespace LGUI
{
    class Window
    {

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        std::vector<UIComponent*> components;
        unsigned long framedelay;
        clock_t startedAt;
        public:


        SDL_Renderer* getRenderer()
        {
            return renderer;
        }

        SDL_Window* getWindow()
        {
            return window;
        }

        Window(std::string& title, int width, int hight, int fps = 60)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
                printf("Error initializing SDL: %s\n", SDL_GetError()); 
            }
            TTF_Init();

            window = SDL_CreateWindow(title.c_str(), 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       width, hight, 0); 
            renderer = SDL_CreateRenderer(window, -1, 0);
            framedelay = 1000/fps;
            setColor(255, 255, 255, 255);
            clearBackground();
            updateScreen();
            startedAt = clock();
        }


        ~Window()
        {
            while(components.size() > 0)
            {
                delete components.back();
                components.pop_back();
            }
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
        }

        void addComponent(UIComponent* component)
        {
            components.push_back(component);
            std::sort (components.begin(), components.end(), UIComponent::compareLayer);
            int dbg;
            //update();
            //updateScreen();
        }
        
        UIComponent* getComponent(unsigned int id)
        {
            for(int i = 0; i < components.size(); i++)
            {
                if(components.at(i)->getId() == id)
                {
                    return components.at(i);
                }
            }
            return NULL;
        }

        std::vector<UIComponent*> getComponents(SDL_Rect area)
        {
            std::vector<UIComponent*> results;
            for(int i = 0; i < components.size(); i++)
            {
                if(components.at(i)->rectIsInBorders(area))
                {
                    results.push_back(components.at(i));
                }
            }
            return results;
        }

        SDL_Rect getRect()
        {
            SDL_Rect winRec;
            SDL_GetWindowSize(window, &winRec.w, &winRec.h);
            SDL_GetWindowPosition(window, &winRec.x, &winRec.y);
            return winRec;
        }

        void setWindowMode(SDL_DisplayMode* mode)
        {
            SDL_SetWindowDisplayMode(window, mode);
        }
        void setFullscreen(bool enable, bool borderlessWindowFullscreen)
        {
            if(enable)
            {
                if(borderlessWindowFullscreen)
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                else
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
            }
            SDL_SetWindowFullscreen(window, 0);
        }
        void setPosition(int x, int y)
        {
            SDL_SetWindowPosition(window, x, y);
        }
        void setSize(int width, int hight)
        {
            SDL_SetWindowSize(window, width, hight);
        }
        void setResizable(bool resizable)
        {
            SDL_SetWindowResizable(window, (SDL_bool)resizable);
        }
        void setTitle(std::string& title)
        {
            SDL_SetWindowTitle(window, title.c_str());
        }

        void setBordered(bool bordered)
        {
            SDL_SetWindowBordered(window, (SDL_bool)(bordered));
        }

        void setShape(SDL_Surface* shape, SDL_WindowShapeMode* mode)
        {
            SDL_SetWindowShape(window, shape, mode);
        }

        void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
        {
            SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        }
        void setColor(RGBA color)
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        }

        void clearBackground()
        {
            SDL_RenderClear(renderer);
        }


        void updateScreen()
        {
            SDL_UpdateWindowSurface(window);
            SDL_RenderPresent(renderer);
            if(clock() - startedAt < framedelay)
            {
                usleep(framedelay - (clock() - startedAt));
            }
            startedAt = clock();
        }      

        
        bool update()
        {
            bool refresh = false;
            setColor(RGBA(255,255,255,255));
            clearBackground();
            
            if (SDL_PollEvent(&event))
            { 
                for(int i = 0; i < components.size(); i++)
                {
                    if(components.at(i)->update(this, event))
                    {
                        refresh = true;
                    }
                }
                if(event.type ==  SDL_QUIT)
                {
                    // handling of close button 
                    return false;
                }
            }
            else
            {
                for(int i = 0; i < components.size(); i++)
                {
                    if(components.at(i)->update(this))
                    {
                        refresh = true;
                    }
                }
            }
            

            
            

            if(refresh)
            {
                //updateScreen();
            }
            //usleep(framedelay);
            return true;
        }


    };


}

