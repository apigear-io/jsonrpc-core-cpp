project(jsonrpc_core)

set(JSON_BuildTests OFF)

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
  # pull nlohmann json as dependency
  message(STATUS "nlohmann_json NOT FOUND, fetching the release package")
  include(FetchContent)
  set(JSON_Install ON)
  FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.7.3)
  FetchContent_MakeAvailable(json)
endif()

set(JSONRPC_SOURCES
        jsonrpc/types.cpp
        jsonrpc/jsonrpc.cpp
        jsonrpc/rpcprotocol.cpp
        jsonrpc/stdoutlogger.cpp
)

add_library (jsonrpc_core STATIC ${JSONRPC_SOURCES})

target_include_directories (jsonrpc_core
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(jsonrpc_core PUBLIC nlohmann_json::nlohmann_json)


# install binary files
install(TARGETS jsonrpc_core
        EXPORT  jsonrpc_coreConfig
        RUNTIME DESTINATION bin COMPONENT Runtime
        LIBRARY DESTINATION lib COMPONENT Runtime
        ARCHIVE DESTINATION lib/jsonrpc_core COMPONENT Development)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h")
include(CMakePackageConfigHelpers)
export(TARGETS
    jsonrpc_core
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/jsonrpc_coreConfig.cmake"
)
install(EXPORT
    jsonrpc_coreConfig
    DESTINATION "lib/jsonrpc_core/cmake"
)
