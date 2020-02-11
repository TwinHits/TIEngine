This is Twin Ion Engine (TIEngine), a 2D game engine utilizing the SFML libray.

It's objective is to do the low level work for you, so that you can focus on
making game objects and gameplay rules, and less on worrying about object
management, logging, window management, and game loops.

This project is cross platform and has been tested on Visual Studio 17.0 and g++
4.8.4.

This engine utilizes
	SFML - 2.5
	Boost - 1.72.0

Windows set up:
1. Clone this repo.
2. Install dependencies into a folder called 'lib'.
	1. sfml
	2. boost
	3. googletest
		1. Modify the cmake root properties for the actual folder names in lib. 
3. Run cmake . to build a visual studio solution.
4. Copy the DLL's for SFML and boost-filesystem to src/Debug.
5. Open the solution and build all.
6. Select TIEngine_run as the start up program and run. A window showing the FPS in the top right hand corner should
   appear.

	Known issues:
	1. Google tests do not get discovered in Visual Studio test explorer.
	5. run TIEngine_tests to see unit tests passing.

Linux set up:
1. Clone this repo
2. Install dependencies into a folder called 'lib'.
	1. sfml
	2. boost
	3. googletest
		1. Modify the cmake root properties for the actual folder names in lib. 
2. Run cmake . to build a MakeFile.
3. Run make to build.
4. Run TIEngine_run to see a window showing the FPS in teh top right hand corner.

In build/ run startproj.sh with the name of your project and the location for
project directory. This will build folder heriarchy, make the default
config.ini, and a starter makefile.

src/main.cpp has an include statement, rewrite it to point to TIEngine.h.
