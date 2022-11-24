set(JSONRPC_SOURCES
        jsonrpc/types.cpp
        jsonrpc/jsonrpc.cpp
        jsonrpc/rpcprotocol.cpp
        jsonrpc/stdoutlogger.cpp
)


add_library (jsonrpc_core STATIC ${JSONRPC_SOURCES})

target_include_directories (jsonrpc_core PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(jsonrpc_core PRIVATE nlohmann_json::nlohmann_json)
