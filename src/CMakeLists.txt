#Source Files and Header Files
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.cpp)
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true ../include/*.h)

#Compile and link shared library
#add_library(lib${CMAKE_PROJECT_NAME} SHARED ${SOURCES})
#target_link_libraries(lib${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio lua53)
#target_link_libraries(lib${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

#Compile and link staic library
#add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})
#target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio lua53)
#target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

#Compile Sanity Check exe
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio lua53)
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )
