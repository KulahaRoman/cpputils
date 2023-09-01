cmake_minimum_required(VERSION 3.8)

project(cpputils-test)

set(CPPUTILS_TEST_SRC	main.cpp
						src/cpputils_test.cpp
)

add_executable(${PROJECT_NAME} ${CPPUTILS_TEST_SRC})

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "/EHsc")
endif()

target_link_libraries(${PROJECT_NAME} cpputils)
target_link_libraries(${PROJECT_NAME} GTest::gtest)

config_compiler_and_linker()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CPPUTILS_INSTALL_BIN})
