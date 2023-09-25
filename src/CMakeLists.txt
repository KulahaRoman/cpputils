cmake_minimum_required(VERSION 3.15)

project(cpputils)

set(CPPUTILS_SRC
			${PROJECT_NAME}/files.cpp
			${PROJECT_NAME}/logger.cpp
			${PROJECT_NAME}/abstractencryptor.cpp
			${PROJECT_NAME}/aes256encryptor.cpp
			${PROJECT_NAME}/aes.cpp
			${PROJECT_NAME}/md5hasher.cpp
			${PROJECT_NAME}/md5.cpp
			${PROJECT_NAME}/sha256hasher.cpp
			${PROJECT_NAME}/sha256.cpp
			${PROJECT_NAME}/binaryarchive.cpp
			${PROJECT_NAME}/countdownlatch.cpp
			${PROJECT_NAME}/serializer.cpp
			${PROJECT_NAME}/endiannessprovider.cpp
)

set(CPPUTILS_HEADERS 
			${PROJECT_NAME}/encryptor.h			
			${PROJECT_NAME}/abstractencryptor.h
			${PROJECT_NAME}/aes256encryptor.h
			${PROJECT_NAME}/countdownlatch.h
			${PROJECT_NAME}/logger.h
			${PROJECT_NAME}/files.h
			${PROJECT_NAME}/hasher.h
			${PROJECT_NAME}/md5hasher.h
			${PROJECT_NAME}/sha256hasher.h
			${PROJECT_NAME}/binaryarchive.h
			${PROJECT_NAME}/serializable.h
			${PROJECT_NAME}/serializer.h
			${PROJECT_NAME}/threadpool.h
)

add_library(${PROJECT_NAME} STATIC ${CPPUTILS_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES ${CPPUTILS_HEADERS} DESTINATION ${CPPUTILS_INSTALL_INCLUDE}/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION ${CPPUTILS_INSTALL_LIB})