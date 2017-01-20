cmake_minimum_required(VERSION 3.0)

project(mongodb_connection_pool)

# Configure required libraries ...
if(UNIX) # Darwing or Linux
    
    find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
    find_package(Threads REQUIRED)

    if(APPLE)
        # Prefer a homebrew version of OpenSSL over the one in /usr/lib
            file(GLOB OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/*)
        # Prefer the latest (make the latest one first)
            list(REVERSE OPENSSL_ROOT_DIR)

        find_package(OpenSSL 1.0.2 REQUIRED)
    else()
        find_package(OpenSSL 1.0.1 REQUIRED)
    endif()

elseif(WIN32) # Windows systems including Win64.
    message(FATAL_ERROR "-- Windows is not supported for now.")
else()
    message(FATAL_ERROR "-- Unsupported platform sorry! :( ")
endif()

# Configure compiler options ...
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    message("-- configuring clang options")
    set(CMAKE_CXX_FLAGS "-arch x86_64 -std=c++11 -stdlib=libc++ -DBOOST_LOG_DYN_LINK -Wno-deprecated-declarations")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

    message("-- configuring gcc options")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -DBOOST_LOG_DYN_LINK")

endif()

# Project construction ...

# source files ...
add_executable(${PROJECT_NAME} ./source/main.cpp
                               ./source/mongodb_pool_singleton.cpp)

# headers search paths ...
set(MONGODB_INCLUDE_DIR "./libs/mongo-cxx-driver/build/install/include/mongocxx/v_noabi")
set(BSONCXX_INCLUDE_DIR "./libs/mongo-cxx-driver/build/install/include/bsoncxx/v_noabi")
set(HEADER_SEARCH_PATHS ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} ${MONGODB_INCLUDE_DIR} ${BSONCXX_INCLUDE_DIR})

# library search paths ...
if(APPLE)
    set(OPENSSL_LIBS "/usr/local/Cellar/openssl/1.0.2f/lib/libssl.1.0.0.dylib;/usr/local/Cellar/openssl/1.0.2f/lib/libcrypto.1.0.0.dylib")
    set(BSONCXX_LIBRARY "${PROJECT_SOURCE_DIR}/libs/mongo-cxx-driver/build/install/lib/libbsoncxx.3.1.1.dylib")
    set(MONGODB_LIBRARY "${PROJECT_SOURCE_DIR}/libs/mongo-cxx-driver/build/install/lib/libmongocxx.3.1.1.dylib")

    set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${BSONCXX_LIBRARY} ${MONGODB_LIBRARY})
else()
    set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
    set(BSONCXX_LIBRARY "${PROJECT_SOURCE_DIR}/libs/mongo-cxx-driver/build/install/lib/libbsoncxx.so")
    set(MONGODB_LIBRARY "${PROJECT_SOURCE_DIR}/libs/mongo-cxx-driver/build/install/lib/libmongocxx.so")

    set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${CPPRESTSDK_LIBRARY} ${BSONCXX_LIBRARY} ${MONGODB_LIBRARY})
endif()

message(BOOST_LIBS " ${Boost_LIBRARIES}")
message(OPENSSL_LIBS " ${OPENSSL_LIBRARIES}")
message(CPPRESTSDK_LIBRARY " ${CPPRESTSDK_LIBRARY}")

include_directories(${HEADER_SEARCH_PATHS})
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
    target_link_libraries(${PROJECT_NAME} "-framework Security")
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")
else()
    target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SARCH_PATHS})
endif()