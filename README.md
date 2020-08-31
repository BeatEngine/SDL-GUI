# SDL-GUI
SDL 2 GUI Project.

Build:

cd SDL2-2.0.12

sudo apt install xorg-dev (REQUIED FOR UBUNTU)

./configure; make;

sudo make install

cd ..

cd SDL2_ttf-2.0.15/external/freetype-2.9.1/

./configure; make;

sudo make install

cd ..

cd ..

./configure; make;

sudo make install

sudo ldconfig (ubuntu)

cd ..

g++ SDLlightGUI.cpp -oSDLlightGUI

<html>
  <h2>Features</h2>
  <h3>Button</h3>
  <h3>InputBox</h3>
  <h3>RadioBox</h3>
  <h3>CheckBox</h3>
  <h3>TabbedContainer</h3>
  <h3>List</h3>
  <h3>SchrollBox (Container)</h3>
  <h3>MenuList & ContextMenu</h3>
  <h3>Sprites (Images (with events))</h3>
</html>

