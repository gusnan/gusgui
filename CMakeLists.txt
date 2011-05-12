#/**
# *
# *	This file is part of GusGui.
# *	Copyright 2011 Andreas Rönnquist
# *
# *	GusGame is free software: you can redistribute it and/or modify
# *	it under the terms of the GNU Lesser General Public License as published by
# *	the Free Software Foundation, either version 3 of the License, or
# *	(at your option) any later version.
# *
# *	GusGame is distributed in the hope that it will be useful,
# *	but WITHOUT ANY WARRANTY; without even the implied warranty of
# *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *	GNU Lesser General Public License for more details.
# *
# *	You should have received a copy of the GNU Lesser General Public License
# *	along with GusGame.  If not, see <http://www.gnu.org/licenses/>.
# *
# */

project (GusGui)

# Require CMake 2.6
cmake_minimum_required(VERSION 2.6)

set(GUSGUI_LIBRARY_NAME gusgui)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

option (DEBUG "Build Debug executable" off)

if (DEBUG)
	message(STATUS "Building Debug executable")
	set(CMAKE_BUILD_TYPE "Debug")
	add_definitions(-D_DEBUG)
	#add_definitions(-Wwrite-strings 
			#-Wextra 
			#-Wall 
			#-Winit-self 
			#-O 
			#-Wno-uninitialized 
			#-Wno-unused-parameter 
			#-Wno-switch
			#-w
			#-Wreturn-type
			#-Weffc++
		#)
	# Cpp only flags: (Will not be applied to C files.)
	# set(CMAKE_CXX_FLAGS -Weffc++)
	
else (DEBUG)
	message(STATUS "Building Release executable")
	#add_definitions(-fomit-frame-pointer)
	set(CMAKE_BUILD_TYPE "Release")
	
endif (DEBUG)
	
set(DLL_FLAGS -DBUILDING_GUSGAME_DLL)

set(BUILD_SHARED_LIBS on)

SET(CMAKE_SHARED_LIBRARY_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CXX_FLAGS} -DBUILDING_GUSGAME_DLL")


# Fix MinGW/MSYS problem-- c:\mingw\bin\..\lib\gcc\mingw32\3.4.5\..\..\..\..\mingw32\bin\ld.exe: 
# warning: auto-importing has been activated without --enable-auto-import 
# specified on the command line.
#
# see 
# http://sourceware.org/ml/binutils/2009-02/msg00341.html
# http://wiki.wxwidgets.org/HowTo:_Install_MSYS_and_MinGW_for_use_with_Eclipse_CDT
#
# for some info.
if (MSYS) 
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-enable-auto-import")
endif (MSYS)


message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")


find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)

find_package(GusGame REQUIRED)

message(STATUS "GusGame Library: ${GUSGAME_LIBRARY}")

include_directories(include ${GUSGAME_INCLUDE_DIR})

include_directories(include ${CMAKE_SOURCE_DIR}/include)
include_directories(include ${CMAKE_SOURCE_DIR}/include/GusGui)


# -------------------------------------------------------
#	Gui Object Source 
# -------------------------------------------------------
set(SRC src/GuiObjects)

set(OBJECT_SOURCES
	${SRC}/Button.cpp
	${SRC}/CheckBox.cpp
	${SRC}/DelayButton.cpp
	${SRC}/FadeButton.cpp
	${SRC}/FileListGui.cpp
	${SRC}/GuiObject.cpp
	${SRC}/InvisibleGuiObject.cpp
	${SRC}/LoaderMeter.cpp
	${SRC}/Panel.cpp
	${SRC}/TextInput.cpp
	${SRC}/TextMarker.cpp
)

#add_library(logLib STATIC ${LOG_SOURCES})


# -------------------------------------------------------
#	"Root"
# -------------------------------------------------------
set(SRC src/)

set(LIB_SOURCES
	${SRC}/GuiData.cpp
	${SRC}/GuiDraw.cpp
	${SRC}/GuiHandler.cpp
	${SRC}/GuiEventHandler.cpp

)

#add_library(exceptionLib STATIC ${EXCEPTION_SOURCES})



#add_library(eventLib STATIC ${EVENTLIB_SOURCES})

set(SOURCES
	${OBJECT_SOURCES}
	${LIB_SOURCES}
)

set(INC include/GusGui)

set(INCLUDE_FILES
	${INC}/Button.h
	${INC}/DelayButton.h  
	${INC}/FileListGui.h  
	${INC}/GuiDraw.h     
	${INC}/GuiLib.h     
	${INC}/GusGui.h              
	${INC}/LoaderMeter.h  
	${INC}/TextInput.h
	${INC}/CheckBox.h  
	${INC}/FadeButton.h   
	${INC}/GuiData.h      
	${INC}/GuiHandler.h  
	${INC}/GuiObject.h  
	${INC}/InvisibleGuiObject.h  
	${INC}/Panel.h        
	${INC}/TextMarker.h
	${SRC}/GuiEventHandler.h
	
)

if (WIN32)
	if (MSYS) 
		Set (WINGL_LIBS glu32 glaux)
	else (MSYS)
		Set (WINGL_LIBS glu32)
	endif (MSYS)

endif(WIN32)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)

find_package(GusGame REQUIRED)

message(STATUS "GusGame Library: ${GUSGAME_LIBRARY}")

#include_directories(include ${SDL_INCLUDE_DIR})
#include_directories(include ${SDL_IMAGE_INCLUDE_DIR})
#include_directories(include ${SDLIMAGE_INCLUDE_DIR})
#include_directories(include ${SDLTTF_INCLUDE_DIR})


include_directories(include ${CMAKE_SOURCE_DIR}/src)
include_directories(include ${CMAKE_SOURCE_DIR}/src/Objects)

include_directories(include ${GUSGAME_INCLUDE_DIR})

if (MSYS)
	message(STATUS "MingDir: $ENV{%MINGDIR%}")
endif (MSYS)

# Print some include dirs
message(STATUS "SDL_INCLUDE_DIR: ${SDL_INCLUDE_DIR}")
message(STATUS "SDL_IMAGE_INCLUDE_DIR: ${SDLIMAGE_INCLUDE_DIR}")

message(STATUS "GUSGAME_INCLUDE_DIR: ${GUSGAME_INCLUDE_DIR}")

# And some libs:

message(STATUS "SDL_LIBRARY: ${SDL_LIBRARY}")
message(STATUS "SDLMAIN_LIBRARY: ${SDLMAIN_LIBRARY}")

message(STATUS "OPENGL_LIBRARY: ${OPENGL_LIBRARY}")
message(STATUS "OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
message(STATUS "GLUT_LIBRARY: ${GLUT_LIBRARY}")

message(STATUS "MY_GLEW_LIB: ${MY_GLEW_LIB}")

if (USE_GLEW) 
	set (MY_GLEW_LIB ${GLEW_LIBRARY})
else (USE_GLEW)
	set (MY_GLEW_LIB )
endif (USE_GLEW)

if (MSYS)
	set (GL_LIBS ${OPENGL_LIBRARY} ${OPENGL_LIBRARIES})
else (MSYS)
	set (GL_LIBS ${OPENGL_LIBRARY})
endif (MSYS)

set(ALL_LIBS 

	${LUA_LIBRARIES}
	${GL_LIBS}
	${GLUT_LIBRARY}
	${WINGL_LIBS}
	${MY_GLEW_LIB}
	${SDLMAIN_LIBRARY}
	${SDL_LIBRARY}
	${SDLTTF_LIBRARY}
   ${SDLIMAGE_LIBRARY}
)

link_libraries(${ALL_LIBS} ${GUSGAME_LIBRARY})

add_library(${GUSGUI_LIBRARY_NAME} SHARED ${SOURCES})
target_link_libraries(${GUSGUI_LIBRARY_NAME})  #${ALL_LIBS})

set(EX_DIR examples)

# link_libraries(${ALL_LIBS})

#add_dependencies(example1 ${LIBRARY_NAME})


include_directories(include ${SDL_INCLUDE_DIR})
include_directories(include ${SDL_IMAGE_INCLUDE_DIR})
include_directories(include ${SDLIMAGE_INCLUDE_DIR})
include_directories(include ${SDLTTF_INCLUDE_DIR})

include_directories(include "/usr/local/include")
include_directories(include ${GUSGAME_INCLUDE})

LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${LIBRARY_OUTPUT_PATH} )

add_executable(example1 WIN32 ${EX_DIR}/example1.cpp)
target_link_libraries(example1 ${ALL_LIBS} ${GUSGUI_LIBRARY_NAME} ${GUSGAME_LIBRARY})

add_executable(example2 WIN32 ${EX_DIR}/example2.cpp)
target_link_libraries(example2 ${ALL_LIBS} ${GUSGUI_LIBRARY_NAME} ${GUSGAME_LIBRARY} )

#add_executable(example3 WIN32 ${EX_DIR}/example3.cpp)
#target_link_libraries(example3 ${ALL_LIBS} ${LIBRARY_NAME})

#add_executable(example4 WIN32 ${EX_DIR}/example4.cpp)
#target_link_libraries(example4 ${ALL_LIBS} ${MY_LIBS} ${LIBRARY_NAME})

install_targets(/lib ${GUSGUI_LIBRARY_NAME})
