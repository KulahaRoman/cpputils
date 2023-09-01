cmake_minimum_required(VERSION 3.8)

project(cpputils)

set(CPPUTILS_SRC
			cpputils/files.cpp
			cpputils/logger.cpp
			cpputils/abstractencryptor.cpp
			cpputils/aes256encryptor.cpp
			cpputils/aes.cpp
			cpputils/md5hasher.cpp
			cpputils/md5.cpp
			cpputils/sha256hasher.cpp
			cpputils/sha256.cpp
			cpputils/binaryarchive.cpp
			cpputils/countdownlatch.cpp
)

add_library(${PROJECT_NAME} STATIC ${CPPUTILS_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CPPUTILS_INSTALL_LIB})