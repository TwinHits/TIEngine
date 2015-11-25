This Twin Ion Engine (TIEngine), a game engine utilizing the SFML libray.

It's objective is to do the low level work for you, so that you can focus on
making game objects and gameplay rules, and less on worrying about object
management, logging, window management, and game loops.

To install, clone to your machine and run 'make'. This will produce a
libTIEngine-debug in bin/. Move to lib folder of your choice.

In build/ run startproj.sh with the name of your project and the location for
project directory. This will build folder heriarchy, make the default
config.ini, and a starter makefile.

Edit the makefile with the name of your executable in place of PROJECTNAME and
the location you picked for the libTIEngine in LIBLOCATION.

src/main.cpp has an include statement, rewrite it to point to TIEngine.h.

See docs for documentation for avaliable classes and methods.
