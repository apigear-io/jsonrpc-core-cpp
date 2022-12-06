
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick WebSockets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick WebSockets REQUIRED)

set(QRPCAPP_SOURCES
        main.cpp
        qjsonrpc.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QRpcApp
        ${QRPCAPP_SOURCES}
    )
else()
    if(ANDROID)
        add_library(QRpcApp SHARED
            ${QRPCAPP_SOURCES}
        )
    else()
        add_executable(QRpcApp
          ${QRPCAPP_SOURCES}
        )
    endif()
endif()

target_compile_definitions(QRpcApp
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QRpcApp
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::WebSockets)


target_link_libraries(QRpcApp PRIVATE jsonrpc_core)
