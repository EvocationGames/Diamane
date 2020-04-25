cmake_minimum_required(VERSION 3.15)
project(Diamane VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# libDiamane
include_directories(${CMAKE_SOURCE_DIR})

if(APPLE)
    set(CMAKE_CXX_FLAGS "-fmodules -fcxx-modules")
    file(GLOB_RECURSE libDiamane_src libDiamane/*.cpp libDiamane/*.mm libDiamane/*.m)
else(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
    file(GLOB_RECURSE libDiamane_src libDiamane/*.cpp)
endif()

add_library(Diamane ${libDiamane_src})

if(UNIX AND NOT APPLE)
    target_link_libraries(Diamane ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
endif()


# DiamaneTestApp
file(GLOB_RECURSE DiamaneTestApp_src DiamaneTestApp/*.cpp)
add_executable(DiamaneTestApp ${DiamaneTestApp_src})
target_link_libraries(DiamaneTestApp Diamane)

# macOS Specific
if(APPLE)
add_custom_command(TARGET DiamaneTestApp
        POST_BUILD
        COMMAND rm -rf "${CMAKE_BINARY_DIR}/DiamaneTestApp.app"
        COMMAND mkdir -p "${CMAKE_BINARY_DIR}/DiamaneTestApp.app/Contents/MacOS"
        COMMAND mkdir -p "${CMAKE_BINARY_DIR}/DiamaneTestApp.app/Contents/Resources"
        COMMAND xcrun -sdk macosx metal -I "${CMAKE_SOURCE_DIR}" -c "${CMAKE_SOURCE_DIR}/libDiamane/platform/macos/metal/shaders.metal" -o "${CMAKE_BINARY_DIR}/DiamaneTestApp.app/Contents/Resources/diamane.air"
        COMMAND xcrun -sdk macosx metallib "${CMAKE_BINARY_DIR}/DiamaneTestApp.app/Contents/Resources/diamane.air" -o "${CMAKE_BINARY_DIR}/DiamaneTestApp.app/Contents/Resources/diamane.metallib"
        COMMAND cp "${CMAKE_BINARY_DIR}/DiamaneTestApp" "${CMAKE_BINARY_DIR}/DiamaneTestApp.app/Contents/MacOS/DiamaneTestApp")
endif()