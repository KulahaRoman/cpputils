cmake_minimum_required(VERSION 3.15)

project(cpputils-test)

set(CPPUTILS_TEST_SRC	main.cpp
						src/binaryarchivetest.cpp
						src/serializertest.cpp
)

add_executable(${PROJECT_NAME} ${CPPUTILS_TEST_SRC})

target_link_libraries(${PROJECT_NAME} cpputils)
target_link_libraries(${PROJECT_NAME} GTest::gtest)

config_compiler_and_linker()

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "/EHsc")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CPPUTILS_INSTALL_BIN})
