cmake_minimum_required(VERSION 3.12)

project(snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(FILTER MY_SOURCES EXCLUDE REGEX ".*/main.cpp$")

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${MY_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(${CMAKE_PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic)

FetchContent_Declare(
	GTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0           # versión estable actual (podés fijar otra)
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(GTest)
target_include_directories(${CMAKE_PROJECT_NAME}_lib BEFORE PUBLIC "${GTest_DIR}/include")

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2            # versión exacta
    GIT_SHALLOW ON            # clon ligero
    EXCLUDE_FROM_ALL          # no compilar automáticamente
    SYSTEM                     # suprime warnings de SFML
)
FetchContent_MakeAvailable(SFML)
target_include_directories(${CMAKE_PROJECT_NAME}_lib BEFORE PUBLIC "${SFML_SOURCE_DIR}/include")

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib
	SFML::Graphics SFML::Window SFML::System)

enable_testing()
add_subdirectory(tests)
