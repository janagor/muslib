add_executable(test_mixer test_mixer.cpp)
target_link_libraries(test_mixer PRIVATE muslib_mixer GTest::GTest GTest::Main)
add_test(NAME test_mixer COMMAND test_mixer)

add_executable(test_transform test_transform.cpp)
target_link_libraries(test_transform PRIVATE muslib_transform GTest::GTest GTest::Main)
add_test(NAME test_transform COMMAND test_transform)
