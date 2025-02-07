cmake_minimum_required(VERSION 3.10)

project(MINIJAM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(libs/raylib)


include_directories(libs/entt/single_include)

include_directories(libs/json/single_include)


include_directories(src/)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
