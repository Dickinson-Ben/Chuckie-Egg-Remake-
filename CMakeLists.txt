project(sdl2template)
cmake_minimum_required(VERSION 3.0)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

ADD_EXECUTABLE(myGame src/main.cpp)
TARGET_LINK_LIBRARIES(myGame ${CONAN_LIBS})

set (CMAKE_CXX_STANDARD 11)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "myGame")

FILE(COPY assets/ DESTINATION bin/assets)
FILE(COPY assets/ DESTINATION bin/bin/assets)
