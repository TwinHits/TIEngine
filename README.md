This is Twin Ion Engine (TIEngine), a 2D game engine utilizing the SFML libray.

It's objective is to do all the low level work for you so that you can focus on making fun games.

This project is cross platform and has been tested on Visual Studio 19.0 and g++
9.3.0.

This engine uses these versions for it's dependenices:
	SFML - 2.5
	Boost - 1.72.0
	sol2 - 3.2.1
		https://github.com/ThePhD/sol2
	Lua - 5.3.5
		https://sourceforge.net/projects/luabinaries/files/5.3.5/

Windows:
1. Clone this repo.
2. Install dependencies into a folder called 'lib' with a folder name with version and -win appened
	ex. SFML-2.5.1-win
3. Run cmake . to build a visual studio solution.
4. Copy the DLL's for SFML, lua, and boost-filesystem to src/Debug.
5. Open the solution and build all.
4. Run Debug to run TIEngine


Linux/WSL:
1. Clone this repo
2. Install dependencies into a folder called 'lib' with a folder name with version and -gnu appened
	ex. SFML-2.5.1-gnu
2. Run cmake . to build a MakeFile.
3. Run make to build.
4. Run ./TIEngine to run TIEngine

Known issues:
1. Google tests do not get discovered in Visual Studio test explorer.
5. run TIEngine_tests to see unit tests passing.
