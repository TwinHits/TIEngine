set(TESTS_PROJECT ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${TESTS_PROJECT} ${TEST_SOURCES})

target_link_libraries(${TESTS_PROJECT} ${CMAKE_PROJECT_NAME} gtest)

enable_testing()
add_test(${TESTS_PROJECT} ${TESTS_PROJECT})
