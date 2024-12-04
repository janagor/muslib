add_executable(test_mixer test_mixer.cpp)
target_link_libraries(test_mixer PRIVATE mixer GTest::GTest GTest::Main)
add_test(NAME test_mixer COMMAND test_mixer)
