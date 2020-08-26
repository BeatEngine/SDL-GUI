#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace LGUI
{

    void renderDrawCircle(SDL_Renderer* renderer, int x0, int y0, float radius, float thickness)
    {
        int f = 1 - radius;
        int ddF_x = 0;
        int ddF_y = -2 * radius;
        int x = 0;
        int y = radius;

        SDL_RenderDrawPoint(renderer, x0, y0 + radius);
        SDL_RenderDrawPoint(renderer, x0, y0 - radius);
        SDL_RenderDrawPoint(renderer, x0 + radius, y0);
        SDL_RenderDrawPoint(renderer, x0 - radius, y0);

        while(x < y)
        {
            if(f >= 0)
            {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x + 1;

            SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
            SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
            SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
            SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
            SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
            SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
            SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
            SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        }
        if(thickness > 0)
        {
            renderDrawCircle(renderer, x0, y0, radius-0.5, thickness-0.5);
        }
    }

    void renderDrawEllipse(SDL_Renderer* renderer, int xm, int ym, float d1, float d2, float thickness)
    {
    int dx = 0, dy = d2; /* im I. Quadranten von links oben nach rechts unten */
    long a2 = d1*d1, b2 = d2*d2;
    long err = b2-(2*d2-1)*a2, e2; /* Fehler im 1. Schritt */

    do {
        SDL_RenderDrawPoint(renderer, xm+dx, ym+dy); /* I. Quadrant */
        SDL_RenderDrawPoint(renderer, xm-dx, ym+dy); /* II. Quadrant */
        SDL_RenderDrawPoint(renderer, xm-dx, ym-dy); /* III. Quadrant */
        SDL_RenderDrawPoint(renderer, xm+dx, ym-dy); /* IV. Quadrant */

        e2 = 2*err;
        if (e2 <  (2*dx+1)*b2) { dx++; err += (2*dx+1)*b2; }
        if (e2 > -(2*dy-1)*a2) { dy--; err -= (2*dy-1)*a2; }
    } while (dy >= 0);

    while (dx++ < d1) { /* fehlerhafter Abbruch bei flachen Ellipsen (b=1) */
        SDL_RenderDrawPoint(renderer, xm+dx, ym); /* -> Spitze der Ellipse vollenden */
        SDL_RenderDrawPoint(renderer, xm-dx, ym);
    }
    if(thickness > 0)
    {
        renderDrawEllipse(renderer, xm, ym, d1-1, d2, thickness-1);
        renderDrawEllipse(renderer, xm, ym, d1, d2-1, thickness-1);
        renderDrawEllipse(renderer, xm, ym, d1-1, d2-1, thickness-1);
    }
    }

    void renderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
    {
        int yy;
        for(int xx = -radius; xx < radius; xx++)
        {
            for(yy = -radius; yy < radius; yy++)
            {
                if(sqrtf(xx*xx+yy*yy) <= radius)
                {
                    SDL_RenderDrawPoint(renderer,x + xx, y + yy);
                }
            }
        }
    }

    void renderFillBoxRounded(SDL_Renderer* renderer, int x, int y, int width, int hight, int roundFactor, int borderX = 999999, int borderY = 999999)
    {
        if(roundFactor > 7)
        {
            SDL_Rect trec;
            trec.x = x;
            trec.y = y;
            trec.w = width;
            trec.h = hight;
            SDL_RenderFillRect(renderer, &trec);
            return;
        }
        int yy;
        int radius = width;
        float tmp;
        float tmp2;
        int cx = x + width/2;
        int cy = y + hight/2;
        int i;
        for(int xx = -width/2; xx < width/2; xx++)
        {
            for(yy = -hight/2; yy < hight/2; yy++)
            {
                tmp = powf(xx, 2*roundFactor)/powf(width/2, 2*roundFactor) + powf(yy, 2*roundFactor)/powf(hight/2, 2*roundFactor);
                if(tmp <= 1 && yy + hight/2 > 0 && xx + width/2 > 0 && xx + width/2 < borderX && yy + hight/2 < borderY)
                {
                    SDL_RenderDrawPoint(renderer,x + xx + width/2 -1, y + yy + hight/2 -1);
                }
            }
        }
    }

    void renderDrawBoxRounded(SDL_Renderer* renderer, int x, int y, int width, int hight, int roundFactor, int thickness, int borderX = 999999, int borderY = 999999)
    {
        if(roundFactor > 7)
        {
            SDL_Rect trec;
            trec.x = x;
            trec.y = y;
            trec.w = width;
            trec.h = hight;
            for(int i = 0; i < thickness; i++)
            {
                SDL_RenderDrawRect(renderer, &trec);
                trec.x += 1;
                trec.y += 1;
                trec.h -= 2;
                trec.w -= 2;
            }
            return;
        }
        int yy;
        int radius = width;
        float tmp;
        float tmp2;
        int cx = x + width/2;
        int cy = y + hight/2;
        int i;
        std::vector<SDL_Point> points;
        for(int xx = -width/2; xx < width/2; xx++)
        {
            for(yy = -hight/2; yy < hight/2; yy++)
            {
                tmp = powf(xx, 2*roundFactor)/powf(width/2, 2*roundFactor) + powf(yy, 2*roundFactor)/powf(hight/2, 2*roundFactor);
                tmp2 = powf(xx, 2*roundFactor)/powf((width-3-thickness)/2, 2*roundFactor) + powf(yy, 2*roundFactor)/powf((hight-3-thickness)/2, 2*roundFactor);
                if(tmp <= 1 && tmp2 > 1 && yy + hight/2 > 0 && xx + width/2 > 0  && xx + width/2 < borderX && yy + hight/2 < borderY)
                {
                    points.push_back(SDL_Point());
                    points.back().x = x + xx + width/2 -1;
                    points.back().y = y + yy + hight/2 -1;
                    //SDL_RenderDrawPoint(renderer,x + xx + width/2 -1, y + yy + hight/2 -1);
                }
            }
        }
        SDL_RenderDrawPoints(renderer, points.data(), points.size());
    }

}


#include "Component.h"
#include "Text.h"
#include "Button.h"
#include "InputBox.h"
#include "RadioBox.h"
#include "RadioGroup.h"
#include "CheckBox.h"
#include "ScrollBar.h"
#include "MenuList.h"
#include "ContextMenu.h"
#include "ProgressBar.h"



/* Containers -------------------  */
#include "List.h"
#include "ScrollBox.h"
#include "TabbedContainer.h"

