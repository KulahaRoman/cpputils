cmake_minimum_required(VERSION 3.8)

project(cpputils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES # Files
			src/utils/files/files.cpp
			
			# Logger
			src/utils/logger/logger.cpp
			
			# Exceptions
			src/utils/exceptions/exception.cpp
			src/utils/exceptions/runtimeexception/runtimeexception.cpp
			
			# Encryptors
			src/utils/encryptors/encryptors.cpp
			src/utils/encryptors/abstract/abstractencryptor.cpp
			src/utils/encryptors/aes256encryptor/aes256encryptor.cpp
			src/utils/encryptors/aes256encryptor/aes.cpp
			
			# Synchronizers
			src/utils/synchronizers/synchronizers.cpp
			src/utils/synchronizers/countdownlatch/countdownlatch.cpp
)

set(HEADERS # Files
			src/utils/files/files.h

			# Logger
			src/utils/logger/logger.h
			
			# Exceptions
			src/utils/exceptions/exception.h
			src/utils/exceptions/exceptions.h
			src/utils/exceptions/exceptiontype.h
			src/utils/exceptions/runtimeexception/runtimeexception.h
			
			# Encryptors
			src/utils/encryptors/iencryptor.h
			src/utils/encryptors/encryptors.h
			src/utils/encryptors/abstract/abstractencryptor.h
			src/utils/encryptors/aes256encryptor/aes256encryptor.h
			src/utils/encryptors/aes256encryptor/aes.h
			
			# Synchronizers
			src/utils/synchronizers/synchronizers.h
			src/utils/synchronizers/countdownlatch/countdownlatch.h
			
			# ThreadPool
			src/utils/threadpool/threadpool.h
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")