
#Settings
cmake_minimum_required(VERSION 3.16.3)
project(TIEngine)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

#Dependencies
#SFML
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set(SFML_DIR "lib/SFML-2.5.1/lib/cmake/SFML")
	include_directories("lib/SFML-2.5.1/include")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(SFML_DIR "lib/SFML-2.5.1-windows-vc15-64-bit/lib/cmake/SFML")
	include_directories("lib/SFML-2.5.1-windows-vc15-64-bit/include")
	#link_directories("lib/SFML-2.5.1-windows-vc15-64-bit/bin" "lib/SFML-2.5.1-windows-vc15-64-bit/lib")
endif()
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#Boost
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set(BOOST_ROOT "lib/boost_1_72_0")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(BOOST_ROOT "lib/boost_1_72_0-msvc-14.2-64")
endif()
find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories("lib/boost_1_72_0-msvc-14.2-64/lib64-msvc-14.2")

#Include
include_directories(include)

#TIEngine Library location
link_directories("src/Debug")

#Call other cmake files
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest)
