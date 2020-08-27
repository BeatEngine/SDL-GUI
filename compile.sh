#/bin/bash
g++ SDLlightGUI.cpp -static-libgcc -static-libstdc++ -lSDL2 -lSDL2main -lSDL2_ttf -o SDLLightGUI
g++ SDLlightGUI.cpp -static-libgcc -static-libstdc++ -lSDL2 lib/libSDL2main.a -lSDL2_ttf -o SDLLightGUIstatic

