cmake_minimum_required(VERSION 3.10)

project(GameEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    set(TARGET_BUILD_PLATFORM "win32")
endif (WIN32)

set( SOURCE_PATH  "code" )

file(GLOB RENDER_H ${SOURCE_PATH}/render/*.hpp)
file(GLOB GLFW_H ${SOURCE_PATH}/GLFW/*.hpp)
file(GLOB ENGINE_H ${SOURCE_PATH}/engine/*.hpp)
file(GLOB_RECURSE ENGINE_SRC ${SOURCE_PATH}/*.cpp)

include_directories(${SOURCE_PATH})
include_directories(${SOURCE_PATH}/GLFW)
include_directories(${SOURCE_PATH}/render)
include_directories(${SOURCE_PATH}/engine)

set(GLFW_PATH "third_party/glfw")
include_directories(${GLFW_PATH}/include)
add_subdirectory(${GLFW_PATH})

set(GLEW_PATH "third_party/glew")
include_directories(${GLEW_PATH}/include)
add_subdirectory(${GLEW_PATH}/build/cmake)


add_executable(GameEngine ${ENGINE_SRC} ${RENDER_H} ${ENGINE_H} ${GLFW_H})

find_package(openGL)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glew_s)