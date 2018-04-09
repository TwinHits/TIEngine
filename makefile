CPP_FILES = ${wildcard src/managers/*.cpp} ${wildcard src/objects/*.cpp} ${wildcard src/utilities/*.cpp} #${wildcard src/*.cpp}
TEST_CPP_FILES = ${wildcard tests/*.cpp}
OBJ_FILES = ${addprefix bin/objs/,${notdir ${CPP_FILES:.cpp=.o}}} ${addprefix bin/tests/,${notdir ${TEST_CPP_FILES:.cpp=.o}}}
CC_FLAGS = -g -Wall -Wno-unused-variable -Werror -std=c++11
LD_FLAGS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lboost_filesystem -lboost_system -lsoci_core -lsoci_postgresql -lgtest -lgtest_main -lpthread -lgmock -lgmock_main
IN_FLAGS = -Iinclude
LIB_NAME = libTIEngine-debug.a

all: bin/tiengine rv

bin/tiengine: ${OBJ_FILES} 
	g++ -o $@ $^ ${LD_FLAGS}

bin/objs/%.o: src/managers/%.cpp
	g++ ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

bin/objs/%.o: src/objects/%.cpp
	g++ ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

bin/objs/%.o: src/utilities/%.cpp
	g++ ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

#bin/objs/%.o: src/%.cpp
#	g++ ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

bin/tests/%.o: tests/%.cpp
	g++ ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

rv:
	ar rvs bin/${LIB_NAME} ${OBJ_FILES}

clean:
	rm bin/objs/*.o
	tm bin/tests/*.o
	rm bin/tiengine
	rm bin/libTIEngine-debug.a
