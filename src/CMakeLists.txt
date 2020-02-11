#Source Files
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.cpp)

#Compile and link shared library
add_library(lib${CMAKE_PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(lib${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio )
target_link_libraries(lib${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

#Compile and link staic library
add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio )
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

#Compile Sanity Check exe
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_run sfml-graphics sfml-audio )
target_link_libraries(${CMAKE_PROJECT_NAME}_run ${Boost_LIBRARIES} )
