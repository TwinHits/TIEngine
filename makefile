CPP_FILES = ${wildcard src/managers/*.cpp} ${wildcard src/objects/*.cpp} 
OBJ_FILES = ${addprefix bin/objs/,${notdir ${CPP_FILES:.cpp=.o}}}
CC_FLAGS = -g -Wall -Werror -std=c++11
LD_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lboost_filesystem -lboost_system

bin/tiengine: ${OBJ_FILES}
	g++ -o $@ $^ ${LD_FLAGS}

bin/objs/%.o: src/managers/%.cpp
	g++ ${CC_FLAGS} -c -o $@ $<

bin/objs/%.o: src/objects/%.cpp
	g++ ${CC_FLAGS} -c -o $@ $<

bin/objs/%.o: client/%.cpp
	g++ ${CC_FLAGS} -c -o $@ $<


CLIENTCPP_FILES = ${wildcard client/*.cpp}
CLIENTOBJ_FILES = ${addprefix bin/objs/,${notdir ${CLIENTCPP_FILES:.cpp=.o}}}

client: ${CLIENTOBJ_FILES} ${OBJ_FILES}
	g++ ${CC_FLAGS} -o bin/client $^ ${LD_FLAGS}


clean:
	rm bin/objs/*.o
	rm bin/client
	rm bin/tiengine
