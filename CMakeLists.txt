cmake_minimum_required(VERSION 3.8)

project(cpputils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES # Files
			src/cpputils/files/files.cpp
			
			# Logger
			src/cpputils/logger/logger.cpp
			
			# Encryptors
			src/cpputils/encryptors/abstract/abstractencryptor.cpp
			src/cpputils/encryptors/aes256encryptor/aes256encryptor.cpp
			src/cpputils/encryptors/aes256encryptor/aes.cpp

			# Hashers
			src/cpputils/hashers/md5hasher/md5hasher.cpp
			src/cpputils/hashers/md5hasher/md5.cpp
			src/cpputils/hashers/sha256hasher/sha256hasher.cpp
			src/cpputils/hashers/sha256hasher/sha256.cpp

			# Serialization
			src/cpputils/serialization/binaryarchive.cpp

			
			# Synchronizers
			src/cpputils/synchronizers/countdownlatch/countdownlatch.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_subdirectory(libs/spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")