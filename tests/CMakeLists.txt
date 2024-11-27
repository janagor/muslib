find_package(GTest REQUIRED)

add_executable(cpp_tests cpp_tests.cpp)
target_link_libraries(cpp_tests PRIVATE cpp_module GTest::GTest GTest::Main)

add_test(NAME cpp_test COMMAND cpp_tests)

