sudo apt install libsdl2-dev
sudo apt install libsdl2-ttf-dev
sudo apt install libsdl2-image-dev

cd ./SDL2-2.0.12
./configure --prefix=/tmp/sdl2-win32 --host=i686-w64-mingw32
make
sudo make install
sudo mv /tmp/sdl2-win32 /usr/local/
./configure --prefix=/tmp/sdl2-win64 --host=x86_64-w64-mingw32
make
sudo make install
sudo mv /tmp/sdl2-win64 /usr/local/
cd ../SDL2_ttf-2.0.15
./configure --prefix=/usr/local/sdl2-ttf-win32
make
sudo make install
sudo mv /tmp/sdl2-ttf-win32 /usr/local/
./configure --prefix=/usr/local/sdl2-ttf-win64
make
sudo make install
sudo mv /tmp/sdl2-ttf-win64 /usr/local/

sudo cp /usr/local/include/SDL2/SDL_ttf.h /usr/local/sdl2-win32/include/SDL_ttf.h
sudo cp /usr/local/lib/libSDL2_ttf.a /usr/local/sdl2-win32/lib/libSDL2_ttf.a
sudo cp -r /usr/local/include/freetype2 /usr/local/sdl2-win32/include/freetype2
sudo cp /usr/local/lib/libfreetype.a /usr/local/sdl2-win32/lib/libfreetype.a
sudo cp /usr/local/lib/libSDL2_ttf.a /usr/local/sdl2-win32/lib/libSDL2_ttf.la
sudo cp /usr/local/lib/libfreetype.a /usr/local/sdl2-win32/lib/libfreetype.la
sudo cp /tmp/sdl2-ttf-win64 /usr/local/
sudo cp /usr/local/include/SDL2/SDL_ttf.h /usr/local/sdl2-win64/include/SDL_ttf.h
sudo cp /usr/local/lib/libSDL2_ttf.a /usr/local/sdl2-win64/lib/libSDL2_ttf.a
sudo cp -r /usr/local/include/freetype2 /usr/local/sdl2-win64/include/freetype2
sudo cp /usr/local/lib/libfreetype.a /usr/local/sdl2-win64/lib/libfreetype.a
sudo cp /usr/local/lib/libSDL2_ttf.a /usr/local/sdl2-win64/lib/libSDL2_ttf.la
sudo cp /usr/local/lib/libfreetype.a /usr/local/sdl2-win64/lib/libfreetype.la


