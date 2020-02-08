This is Twin Ion Engine (TIEngine), a 2D game engine utilizing the SFML libray.

It's objective is to do the low level work for you, so that you can focus on
making game objects and gameplay rules, and less on worrying about object
management, logging, window management, and game loops.

This project is cross platform and has been tested on Visual Studio 14.0 and gcc
4.8.4.

Install the dependencies in the lib folder.
This engine utilizes
	SFML - 2.5
	Boost - 1.72.0

To install, clone to your machine and run 'cmake .'. This will create a TIEngine library and unit tests.

In build/ run startproj.sh with the name of your project and the location for
project directory. This will build folder heriarchy, make the default
config.ini, and a starter makefile.

src/main.cpp has an include statement, rewrite it to point to TIEngine.h.

See docs for documentation for avaliable classes and methods.

