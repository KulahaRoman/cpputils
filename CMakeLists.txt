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
			src/cpputils/encryptors/encryptors.cpp
			src/cpputils/encryptors/abstract/abstractencryptor.cpp
			src/cpputils/encryptors/aes256encryptor/aes256encryptor.cpp
			src/cpputils/encryptors/aes256encryptor/aes.cpp
			
			# Synchronizers
			src/cpputils/synchronizers/synchronizers.cpp
			src/cpputils/synchronizers/countdownlatch/countdownlatch.cpp
)

set(HEADERS # Files
			src/cpputils/files/files.h

			# Logger
			src/cpputils/logger/logger.h

			# Serialization
			src/cpputils/serialization/iserializable.h
			
			# Exceptions
			src/cpputils/exceptions/exception.h
			src/cpputils/exceptions/exceptions.h
			src/cpputils/exceptions/exceptiontype.h
			src/cpputils/exceptions/runtimeexception/runtimeexception.h
			
			# Encryptors
			src/cpputils/encryptors/iencryptor.h
			src/cpputils/encryptors/encryptors.h
			src/cpputils/encryptors/abstract/abstractencryptor.h
			src/cpputils/encryptors/aes256encryptor/aes256encryptor.h
			src/cpputils/encryptors/aes256encryptor/aes.h
			
			# Synchronizers
			src/cpputils/synchronizers/synchronizers.h
			src/cpputils/synchronizers/countdownlatch/countdownlatch.h
			
			# ThreadPool
			src/cpputils/threadpool/threadpool.h
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")