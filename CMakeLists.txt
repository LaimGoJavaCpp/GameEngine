cmake_minimum_required(VERSION 3.10)

project(GameEngine)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Определение платформы
if (WIN32)
    set(TARGET_BUILD_PLATFORM "win32")
elseif (UNIX)
    set(TARGET_BUILD_PLATFORM "linux")
endif()

# Пути к исходному коду
set(SOURCE_PATH "code")

# Файлы исходников и заголовков
file(GLOB RENDER_H ${SOURCE_PATH}/render/*.hpp)
file(GLOB GLFW_H ${SOURCE_PATH}/GLFW/*.hpp)
file(GLOB ENGINE_H ${SOURCE_PATH}/engine/*.hpp)
file(GLOB_RECURSE ENGINE_SRC ${SOURCE_PATH}/*.cpp)

# Подключение директорий для include
include_directories(${SOURCE_PATH})
include_directories(${SOURCE_PATH}/GLFW)
include_directories(${SOURCE_PATH}/render)
include_directories(${SOURCE_PATH}/engine)

# GLFW
set(GLFW_PATH "third_party/glfw")
include_directories(${GLFW_PATH}/include)
add_subdirectory(${GLFW_PATH})

# GLEW
set(GLEW_PATH "third_party/glew")
include_directories(${GLEW_PATH}/include)

# Ручная линковка GLEW (GLEW должен быть собран для Linux)
if (UNIX)
    add_library(glew_s STATIC IMPORTED)
    set_target_properties(glew_s PROPERTIES
        IMPORTED_LOCATION ${GLEW_PATH}/lib/libGLEW.a
        INTERFACE_INCLUDE_DIRECTORIES ${GLEW_PATH}/include
    )
else()
    add_subdirectory(${GLEW_PATH}/build/cmake)
endif()

# Добавление исполняемого файла
add_executable(GameEngine ${ENGINE_SRC} ${RENDER_H} ${ENGINE_H} ${GLFW_H})

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(GameEngine ${OPENGL_LIBRARIES})

# Линковка GLFW и GLEW
target_link_libraries(GameEngine glfw)
target_link_libraries(GameEngine glew_s)

# Установка директорий вывода
set_target_properties(GameEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
