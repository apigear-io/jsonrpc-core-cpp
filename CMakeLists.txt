cmake_minimum_required(VERSION 3.14)
option(BUILD_EXAMPLES "Build examples" TRUE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(jsonrpc-core-cpp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory (src)

if(BUILD_EXAMPLES)
add_subdirectory (examples/QRpcApp)
endif()
