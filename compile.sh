#/bin/bash
g++ SDLlightGUI.cpp -static-libgcc -static-libstdc++ -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -o SDLLightGUI
g++ SDLlightGUI.cpp -static-libgcc -static-libstdc++ -lSDL2 lib/libSDL2main.a -lSDL2_ttf lib/libSDL2_image.a -o SDLLightGUIstatic

