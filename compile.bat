cd ..\MinGW\bin\
mingw32-g++.exe ../../SDL-GUI-master\SDLlightGUI.cpp -w -m32 -fpermissive -static-libgcc -static-libstdc++ -lmingw32 -Wl,-subsystem,windows -lSDL2main -lSDL2 -lSDL2_ttf -o ../../SDL-GUI-master/win32/SDLlightGUI_32.exe
cd ..\mingw64\bin\
x86_64-w64-mingw32-g++.exe ../../../SDL-GUI-master\SDLlightGUI.cpp -w -m64 -fpermissive -static-libgcc -static-libstdc++ -lmingw32 -Wl,-subsystem,windows -lSDL2main -lSDL2 -lSDL2_ttf -o ../../../SDL-GUI-master/win64/SDLlightGUI_64.exe
cd ..\..\..\SDL-GUI-master
pause