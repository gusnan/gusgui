
# GusGui

On Windows 10, MSYS2, I am successful building using this cmake:

``cmake .. -DALLEGRO_INCLUDE_DIR="C:/msys64/mingw64/include/" \
-DALLEGRO_LIBRARIES=/mingw64/lib/liballegro_monolith.dll.a \
-G"MSYS Makefiles" \
-DGUSGAME_INCLUDE_DIR=../../../gusgame/gusgame/include \
-DGUSGAME_LIBRARY=../../../gusgame/gusgame/lib/libgusgame.a``

