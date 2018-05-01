#5/1/2018 I think that SFML 2.4.2 is compiled with g++-4.8, so I had to explicitly use g++ because the default is now 5. I think since I compiled gtest and gmock with 4.8, it also needs 4.8.
#But I need at least 4.8 because I need make_unique. I made my own.
#Now, Gtest isn't working again probably because my default is 5.0.
#Recompiled gtest on 4.8. Had to delete the existing ones in my lib in order for the changes to take effect.

CPP_FILES = ${wildcard src/managers/*.cpp} ${wildcard src/objects/*.cpp} ${wildcard src/utilities/*.cpp} #${wildcard src/*.cpp}
TEST_CPP_FILES = ${wildcard tests/*.cpp}
OBJ_FILES = ${addprefix bin/objs/,${notdir ${CPP_FILES:.cpp=.o}}} ${addprefix bin/tests/,${notdir ${TEST_CPP_FILES:.cpp=.o}}}
CC_FLAGS = -g -Wall -Wno-unused-variable -Werror -std=c++11
LD_FLAGS = -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lboost_filesystem -lboost_system -lsoci_core -lsoci_postgresql -lgtest -lgtest_main -lpthread -lgmock -lgmock_main
IN_FLAGS = -Iinclude -I/usr/local/include/soci -I/usr/local/include/soci/postgresql -I/usr/include/postgresql
LIB_NAME = libTIEngine-debug.a

all: bin/tiengine rv

bin/tiengine: ${OBJ_FILES} 
	g++-4.8 -o $@ $^ ${LD_FLAGS}

bin/objs/%.o: src/managers/%.cpp
	g++-4.8 ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

bin/objs/%.o: src/objects/%.cpp
	g++-4.8 ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

bin/objs/%.o: src/utilities/%.cpp
	g++-4.8 ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

#bin/objs/%.o: src/%.cpp
#	g++-4.8 ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

bin/tests/%.o: tests/%.cpp
	g++-4.8 ${CC_FLAGS} ${IN_FLAGS} -c -o $@ $<

rv:
	ar rvs bin/${LIB_NAME} ${OBJ_FILES}

clean:
	rm bin/objs/*.o
	rm bin/tests/*.o
	rm bin/tiengine
	rm bin/libTIEngine-debug.a
