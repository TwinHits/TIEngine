COMPILER = g++
STANDARD = -std=c++11
DEBUG = -g -Wall -Werror
OBJPATH = bin/objs
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = ${COMPILER} ${STANDARD} ${DEBUG}

OBJECTS = ${OBJPATH}/configmanager.o ${OBJPATH}/scenemanager.o ${OBJPATH}/logmanager.o ${OBJPATH}/assetsmanager.o ${OBJPATH}/sceneobjectmanager.o ${OBJPATH}/windowmanager.o ${OBJPATH}/sceneobject.o ${OBJPATH}/playermanager.o ${OBJPATH}/hashmanager.o ${OBJPATH}/player.o ${OBJPATH}/main.o

all: tiengine

tiengine: configmanager logmanager scenemanager assetsmanager sceneobjectmanager windowmanager playermanager hashmanager sceneobject player main
	${FLAGS} ${OBJECTS} ${LIBS} -o bin/tiengine 

main:
	${FLAGS} -c src/main.cpp -o ${OBJPATH}/main.o

#Managers
logmanager:
	${FLAGS} -c src/managers/LogManagerImplementation.cpp -o ${OBJPATH}/logmanager.o

configmanager:
	${FLAGS} -c src/managers/ConfigManagerImplementation.cpp -o ${OBJPATH}/configmanager.o

assetsmanager:
	${FLAGS} -c src/managers/AssetsManagerImplementation.cpp -o ${OBJPATH}/assetsmanager.o

windowmanager:
	${FLAGS} -c src/managers/WindowManagerImplementation.cpp -o ${OBJPATH}/windowmanager.o

scenemanager:
	${FLAGS} -c src/managers/SceneManagerImplementation.cpp -o ${OBJPATH}/scenemanager.o
	
sceneobjectmanager:
	${FLAGS} -c src/managers/SceneObjectManagerImplementation.cpp -o ${OBJPATH}/sceneobjectmanager.o

playermanager:
	${FLAGS} -c src/managers/PlayerManagerImplementation.cpp -o ${OBJPATH}/playermanager.o

hashmanager:
	${FLAGS} -c src/managers/HashManagerImplementation.cpp -o ${OBJPATH}/hashmanager.o

#Objects
sceneobject:
	${FLAGS} -c src/objects/SceneObjectImplementation.cpp -o ${OBJPATH}/sceneobject.o

player:
	${FLAGS} -c src/objects/PlayerImplementation.cpp -o ${OBJPATH}/player.o


#Utility
clean:
	rm bin/objs/*.o
