cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CONAN_INCLUDE_DIRS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/date_time_zonespec.csv
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(Server main.cpp src/Server.cpp include/Server.hpp src/Session.cpp include/Session.hpp )
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})