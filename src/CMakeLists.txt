
#Source Files
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.cpp)

#Compile and Link library
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio )
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

#Compile Sanity Check
#add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})
#target_link_libraries(${CMAKE_PROJECT_NAME}_run sfml-graphics sfml-audio )
#target_link_libraries(${CMAKE_PROJECT_NAME}_run ${Boost_LIBRARIES} )
