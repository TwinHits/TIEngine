#Test project name
set(TESTS_PROJECT ${CMAKE_PROJECT_NAME}_tests)

#Source files
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})

#Executable and link gtest
add_executable(${TESTS_PROJECT} ${TEST_SOURCES})
target_link_libraries(${TESTS_PROJECT} ${CMAKE_PROJECT_NAME} gtest)

#Artifact from trying to get Visual Studio unit tests to work
enable_testing()
add_test(${TESTS_PROJECT} ${TESTS_PROJECT})
