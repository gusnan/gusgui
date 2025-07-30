
# GusGui

On Windows 10, MSYS2, I am successful building using this cmake:

``cmake .. -DALLEGRO_INCLUDE_DIR="C:/msys64/mingw64/include/" \
-DALLEGRO_LIBRARIES=/mingw64/lib/liballegro_monolith.dll.a \
-G"MSYS Makefiles" \
-DGUSGAME_INCLUDE_DIR=../../../gusgame/gusgame/include \
-DGUSGAME_LIBRARY=../../../gusgame/gusgame/lib/libgusgame.a``



## Tips

To make better encapsulation, you can make a panel class of your own inhertit
from both the Panel class, and the GuiEventHandler class, which makes it
possible to create Event objects in the class and set them as events for the
e.g. Buttons, and still be able to reach those simply in the event handler, and
not use some complicated way to move a Event object between potentially
separated classes.
