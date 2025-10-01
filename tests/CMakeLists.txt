find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(runTests ${TEST_SOURCES})

target_link_libraries(runTests PRIVATE ${CMAKE_PROJECT_NAME}_lib GTest::GTest GTest::Main pthread)

include(GoogleTest)
gtest_discover_tests(runTests)
