COMPILER = g++
STANDARD = -std=c++11
DEBUG = -g -Wall -Werror
OBJPATH = bin/objs
OBJECTS = ${OBJPATH}/configmanager.o ${OBJPATH}/scenemanager.o ${OBJPATH}/logmanager.o ${OBJPATH}/assetsmanager.o ${OBJPATH}/main.o
FLAGS = ${COMPILER} ${STANDARD} ${DEBUG}

all: tiengine

tiengine: configmanager logmanager scenemanager assetsmanager main
	${FLAGS} ${OBJECTS} -o bin/tiengine

main:
	${FLAGS} -c src/main.cpp -o ${OBJPATH}/main.o

scenemanager:
	${FLAGS} -c src/managers/SceneManagerImplementation.cpp -o ${OBJPATH}/scenemanager.o

logmanager:
	${FLAGS} -c src/managers/LogManagerImplementation.cpp -o ${OBJPATH}/logmanager.o

configmanager:
	${FLAGS} -c src/managers/ConfigManagerImplementation.cpp -o ${OBJPATH}/configmanager.o

assetsmanager:
	${FLAGS} -c src/managers/AssetsManagerImplementation.cpp -o ${OBJPATH}/assetsmanager.o

clean:
	rm bin/objs/*.o
