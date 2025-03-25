#pragma once

// 添加这些定义来解决兼容性问题
#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_INTERNAL_

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "request/CancelOrderRequest.h"
#include "request/CancelOrdersRequest.h"

namespace rapdix {
namespace websocket {
namespace request {

class PlaceOrderRequest;
class CancelOrderRequest;

} // namespace request

using json = nlohmann::json;
namespace asio = websocketpp::lib::asio;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// 回调函数类型定义
typedef std::function<void(const std::string&)> MessageCallback;
typedef std::function<void()> ConnectionCallback;
typedef std::function<void(const std::string&)> ErrorCallback;
typedef std::function<void()> CloseCallback;

// 修改类型定义
typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<asio::ssl::context> context_ptr;

class WebSocketClient {
public:
    WebSocketClient(const std::string& uri, 
                   const std::string& apiKey, 
                   const std::string& secretKey);
    ~WebSocketClient();

    bool connect();
    void disconnect();
    bool send(const std::string& message);
    bool isConnected() const;

    void setMessageCallback(MessageCallback callback);
    void setConnectionCallback(ConnectionCallback callback);
    void setErrorCallback(ErrorCallback callback);
    void setCloseCallback(CloseCallback callback);

    bool placeOrder(const request::PlaceOrderRequest& request);
    bool cancelOrder(const request::CancelOrderRequest& request);
    bool cancelOrders(const request::CancelOrdersRequest& request);

private:
    void init();
    context_ptr onTlsInit(websocketpp::connection_hdl hdl);
    void onOpen(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, message_ptr msg);
    void onClose(websocketpp::connection_hdl hdl);
    void onFail(websocketpp::connection_hdl hdl);
    void sendLoginRequest();
    std::string generateSignature(const std::string& message);
    void startHeartbeatThread();
    void heartbeatThread();
    void stopHeartbeat();

private:
    std::string uri_;
    std::string apiKey_;
    std::string secretKey_;
    
    client endpoint_;
    websocketpp::connection_hdl connection_;
    std::thread asioThread_;
    std::thread heartbeatThread_;
    
    bool connected_;
    std::mutex mutex_;
    std::condition_variable cv_;
    
    MessageCallback messageCallback_;
    ConnectionCallback connectionCallback_;
    ErrorCallback errorCallback_;
    CloseCallback closeCallback_;
    
    bool stopHeartbeat_;
};

} // namespace websocket
} // namespace rapdix 