COMPILER = g++
STANDARD = -std=c++11
DEBUG = -g -Wall -Werror
OBJECTS = bin/configmanager.o bin/scenemanager.o bin/logmanager.o bin/main.o 
FLAGS = ${COMPILER} ${STANDARD} ${DEBUG}

all: tiengine

tiengine: configmanager logmanager scenemanager main
	${FLAGS} ${OBJECTS} -o bin/tiengine

main:
	${FLAGS} -c src/main.cpp -o bin/main.o

scenemanager:
	${FLAGS} -c src/managers/SceneManagerImplementation.cpp -o bin/scenemanager.o

logmanager:
	${FLAGS} -c src/managers/LogManagerImplementation.cpp -o bin/logmanager.o

configmanager:
	${FLAGS} -c src/managers/ConfigManagerImplementation.cpp -o bin/configmanager.o

clean:
	rm bin/*.o bin/tiengine
