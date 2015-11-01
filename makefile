CPP_FILES = ${wildcard src/managers/*.cpp} ${wildcard src/objects/*.cpp} ${wildcard src/*.cpp}
OBJ_FILES = ${addprefix bin/objs/,${notdir ${CPP_FILES:.cpp=.o}}}
CC_FLAGS = -g -Wall -Werror -std=c++11
LD_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

tiengine: ${OBJ_FILES}
	g++ -o $@ $^ ${LD_FLAGS}

bin/objs/%.o: src/%.cpp
	g++ ${CC_FLAGS} -c -o $@ $<

bin/objs/%.o: src/managers/%.cpp
	g++ ${CC_FLAGS} -c -o $@ $<

bin/objs/%.o: src/objects/%.cpp
	g++ ${CC_FLAGS} -c -o $@ $<

clean:
	rm bin/objs/*.o
