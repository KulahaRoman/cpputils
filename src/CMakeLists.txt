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
			cpputils/serializer.cpp
			cpputils/endiannessprovider.cpp
)

set(CPPUTILS_HEADERS 
			cpputils/encryptor.h			
			cpputils/abstractencryptor.h
			cpputils/aes256encryptor.h
			cpputils/countdownlatch.h
			cpputils/logger.h
			cpputils/files.h
			cpputils/hasher.h
			cpputils/md5hasher.h
			cpputils/sha256hasher.h
			cpputils/binaryarchive.h
			cpputils/serializable.h
			cpputils/serializer.h
			cpputils/threadpool.h
)

if(NOT TARGET ${PROJECT_NAME})
	add_library(${PROJECT_NAME} STATIC ${CPPUTILS_SRC})
	target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

	install(FILES ${CPPUTILS_HEADERS} DESTINATION ${CPPUTILS_INSTALL_INCLUDE})
	install(TARGETS ${PROJECT_NAME} DESTINATION ${CPPUTILS_INSTALL_LIB})
endif()