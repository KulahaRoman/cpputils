project(cpptuilstest)


set(TEST1_SRC main.cpp)
add_executable(test1 ${TEST1_SRC})
target_link_libraries(test1 GTest::gtest_main cpputils)

add_test(NAME Test1 COMMAND test1)