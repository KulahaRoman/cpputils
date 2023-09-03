cmake_minimum_required(VERSION 3.15)

project(lib-cpputils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPPUTILS_INSTALL_BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CPPUTILS_INSTALL_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CPPUTILS_INSTALL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(libs/spdlog)
add_subdirectory(libs/gtest)

add_subdirectory(src)
add_subdirectory(test)