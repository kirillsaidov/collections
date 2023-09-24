cmake_minimum_required(VERSION 3.5)

# project name init
project(
    zhbk1
	VERSION 1.0
	DESCRIPTION ""
	LANGUAGES C
)

# setting default build type
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)   # for libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # for binaries

# find dependencies
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

if(WIN32)
	find_library(MYSQL_LIBRARY NAMES "libmysql.dll" PATHS "${PROJECT_SOURCE_DIR}/lib")
	set(MySQL_INCLUDE_DIRS "")
	set(MySQL_LIBRARIES "${PROJECT_SOURCE_DIR}/lib/libmysql.dll")

	set(CMAKE_C_FLAGS "-mwindows")
else()
	find_package(MySQL REQUIRED)
endif()

# if(APPLE)
# 	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lm -lGLEW -L/usr/local/lib")
# endif()

# if(UNIX AND NOT APPLE)
# 	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lglfw -lGL -lm -lGLU -lGLEW")
# endif()

# finding all headers and sources
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/inc/*.h)

# include directories
include_directories(${PROJECT_SOURCE_DIR}/inc/)
include_directories(${PROJECT_SOURCE_DIR}/third_party/)
include_directories(${MySQL_INCLUDE_DIRS})

# building library/binary
# add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS}) # for libraries
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})   # for binaries
target_link_libraries(
	${PROJECT_NAME} 
	${PROJECT_SOURCE_DIR}/lib/libvita.a 
	${MySQL_LIBRARIES} 
	glfw OpenGL::GL GLEW::GLEW
)

