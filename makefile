COMPILER = g++
STANDARD = -std=c++11
DEBUG = -g -Wall -Werror
OBJECTS = bin/scenemanager.o bin/main.o
FLAGS = ${COMPILER} ${STANDARD} ${DEBUG}

all: tiengine

tiengine: main scenemanager
	${FLAGS} ${OBJECTS} -o bin/tiengine

main:
	${FLAGS} -c src/main.cpp -o bin/main.o

scenemanager:
	${FLAGS} -c src/managers/SceneManagerImplementation.cpp -o bin/scenemanager.o

clean:
	rm bin/*.o bin/tiengine
