<img src="https://github.com/TwinHits/TIEngine/blob/master/assets/textures/logo.png" alt="TIEngine Logo"
	title="TIEngine Logo" width="350" />
# TIEngine

This is Twin Ion Engine (TIEngine), a 2D game engine utilizing the SFML libray. 

It's objective is to do all the low level work for you so that you can focus on making fun games.

Write your game logic entirely in Lua and use features TIEngine provides to run your game.

This project is cross platform and has been tested on Visual Studio 19.0 and g++
9.3.0.

## Installation
This engine uses these versions for it's dependenices:
	* SFML - 2.5
	* Boost - 1.72.0
	* sol2 - 3.2.1
		https://github.com/ThePhD/sol2
	* Lua - 5.3.5
		https://sourceforge.net/projects/luabinaries/files/5.3.5/

# Windows:
1. Clone this repo.
1. Install dependencies into a folder called 'lib' with a folder name with version and -win appened
	ex. SFML-2.5.1-win
1. Run cmake . to build a visual studio solution.
1. Copy the DLL's for SFML, lua, and boost-filesystem to src/Debug.
1. Open the solution and build all.
1. Run Debug to run TIEngine


# Linux/WSL:
1. Clone this repo
1. Install dependencies into a folder called 'lib' with a folder name with version and -gnu appened
	ex. SFML-2.5.1-gnu
1. Run cmake . to build a MakeFile.
1. Run make to build.
1. Run ./TIEngine to run TIEngine


## Usage

1. Copy config.ini.sample into a config.ini file with your preferred options.
1. Replace the StartUpScript config.ini parameter to your lua script.
1. See the docs for the TIEngine and TIEntity interface.

## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>.
