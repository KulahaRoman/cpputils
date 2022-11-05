cmake_minimum_required(VERSION 3.8)

project(cpputils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES # Files
			src/cpputils/files/files.cpp
			
			# Logger
			src/cpputils/logger/logger.cpp
			
			# Exceptions
			src/cpputils/exceptions/exception.cpp
			src/cpputils/exceptions/runtimeexception/runtimeexception.cpp
			
			# Encryptors
			src/cpputils/encryptors/abstract/abstractencryptor.cpp
			src/cpputils/encryptors/aes256encryptor/aes256encryptor.cpp
			src/cpputils/encryptors/aes256encryptor/aes.cpp
			
			# Synchronizers
			src/cpputils/synchronizers/countdownlatch/countdownlatch.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")