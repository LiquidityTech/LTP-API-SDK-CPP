cmake_minimum_required(VERSION 3.10)
project(rapdix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

set(LIB_SOURCES
    rapdix/util/HttpUtil.cpp
    rapdix/util/SignatureUtil.cpp
    rapdix/service/order/OrderService.cpp
    rapdix/service/account/AccountService.cpp
    rapdix/service/asset/AssetService.cpp
    rapdix/service/position/PositionService.cpp
    rapdix/service/transaction/TransactionService.cpp
    rapdix/service/statement/StatementService.cpp
    rapdix/service/rules/RulesService.cpp
)

set(BROKER_SERVICE_SOURCES
    rapdix/service/broker/BrokerService.cpp
)

set(WEBSOCKET_SOURCES
    rapdix/websocket/WebSocketClient.cpp
    rapdix/websocket/WebSocketDemo.cpp
)

set(SOURCES
    ${LIB_SOURCES}
    ${BROKER_SERVICE_SOURCES}
    ${WEBSOCKET_SOURCES}
)

# 创建静态库
add_library(rapdix_lib STATIC ${SOURCES})

# 设置库的包含目录
target_include_directories(rapdix_lib PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
    /opt/homebrew/include
)

target_link_libraries(rapdix_lib PUBLIC
    ${CURL_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)

add_executable(rapdix rapdix/client/main.cpp)
target_link_libraries(rapdix PRIVATE rapdix_lib)

# 创建统一的测试可执行文件
add_executable(test 
    rapdix/client/test.cpp
)
target_link_libraries(test PRIVATE rapdix_lib)

set(WEBSOCKETPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/websocketpp" CACHE PATH "WebSocket++ include directory")

add_executable(websocket_demo ${WEBSOCKET_SOURCES})
target_link_libraries(websocket_demo PRIVATE 
    rapdix_lib 
    ${OPENSSL_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)
target_include_directories(websocket_demo PRIVATE 
    ${OPENSSL_INCLUDE_DIR}
    ${WEBSOCKETPP_INCLUDE_DIR}
)

add_executable(public_websocket_demo
    rapdix/websocket/public/PublicWebSocketDemo.cpp
    rapdix/websocket/public/PublicWebSocketClient.cpp
)

target_compile_definitions(public_websocket_demo 
    PRIVATE 
    ASIO_STANDALONE
    _WEBSOCKETPP_CPP11_STRICT_
)

target_link_libraries(public_websocket_demo
    PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    ${CMAKE_THREAD_LIBS_INIT}
    ZLIB::ZLIB
)

target_include_directories(public_websocket_demo
    PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${WEBSOCKETPP_INCLUDE_DIR}
    /opt/homebrew/include
) 