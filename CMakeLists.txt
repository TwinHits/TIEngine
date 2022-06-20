#Settings
cmake_minimum_required(VERSION 3.23)
project(TIEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

#Dependencies
	#SFML
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		set(SFML_DIR "lib/SFML-2.5.1-gnu/lib/cmake/SFML")
		include_directories("lib/SFML-2.5.1-gnu/include")
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		set(SFML_DIR "lib/SFML-2.5.1-win/lib/cmake/SFML")
		include_directories("lib/SFML-2.5.1-win/include")
		#link_directories("lib/SFML-2.5.1-win/bin" "lib/SFML-2.5.1-win/lib")
	endif()
	find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

	#Boost
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		set(BOOST_ROOT "lib/boost_1_72_0-gnu")
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		set(BOOST_ROOT "lib/boost_1_72_0-win")
	endif()
	find_package(Boost COMPONENTS filesystem REQUIRED)
	include_directories( ${Boost_INCLUDE_DIR} )
	#link_directories("lib/boost_1_72_0-msvc-14.2-64/lib64-msvc-14.2")
	link_directories("lib/boost_1_72_0-win/stage/lib")

	#Sol3
	include_directories("lib/sol3/include")
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		include_directories("lib/lua-5.3.5-gnu/include")
		link_directories("lib/lua-5.3.5-gnu")
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		include_directories("lib/lua-5.3.5-win/include")
		link_directories("lib/lua-5.3.5-win")
	endif()

	#Pybind11
	#find_package(pybind11 REQUIRED)

#SLN Fine tuning
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

#Include TIEngine directories
include_directories(include)

#Compile TIEngine
#Source Files and Header Files
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.cpp)
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true include/*.h)

#Compile and link shared library
#add_library(lib${CMAKE_PROJECT_NAME} SHARED ${SOURCES})
#target_link_libraries(lib${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio lua53)
#target_link_libraries(lib${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

#Compile and link staic library
#add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})
#target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio lua53)
#target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

#Compile Check exe
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio lua53)
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )

source_group(TREE src FILES ${SOURCES})
source_group(TREE include FILES ${HEADERS})

#add_subdirectory(tests)
#add_subdirectory(lib/googletest)
