cmake_minimum_required(VERSION 3.16.3)

#Settings
project(TIEngine)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

#Dependencies: SFML
set(SFML_DIR "lib/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#Boost
set(BOOST_ROOT "lib/boost_1_72_0")
find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

#Include
include_directories(include)

#Call other cmake files
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest)
