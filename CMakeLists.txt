cmake_minimum_required(VERSION 3.28)

project(snake VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(FILTER MY_SOURCES EXCLUDE REGEX ".*/main.cpp$")

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${MY_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(${CMAKE_PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs" FORCE)

FetchContent_Declare(
	GTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0           # versión estable actual (podés fijar otra)
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(GTest)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2            # versión exacta
    GIT_SHALLOW ON            # clon ligero
    EXCLUDE_FROM_ALL          # no compilar automáticamente
    SYSTEM                     # suprime warnings de SFML
)
FetchContent_MakeAvailable(SFML)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_lib PUBLIC
	SFML::Graphics SFML::Window SFML::System)
target_compile_features(${CMAKE_PROJECT_NAME}_lib PUBLIC cxx_std_17)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)

enable_testing()
add_subdirectory(tests)
