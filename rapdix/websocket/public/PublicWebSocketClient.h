#pragma once
#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

namespace rapdix {
namespace websocket {
namespace public_api {

using websocketpp::client;
using websocketpp::config::asio_tls_client;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef client<asio_tls_client> client_type;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
typedef client_type::message_ptr message_ptr;

typedef std::function<void(const std::string&)> MessageCallback;
typedef std::function<void(const std::string&)> ConnectionCallback;
typedef std::function<void(const std::string&)> ErrorCallback;
typedef std::function<void(const std::string&)> CloseCallback;

class PublicWebSocketClient {
public:
    explicit PublicWebSocketClient(const std::string& host);
    ~PublicWebSocketClient();

    bool connect();
    void disconnect();
    bool isConnected() const;
    bool send(const std::string& message);

    void setMessageCallback(MessageCallback callback);
    void setConnectionCallback(ConnectionCallback callback);
    void setErrorCallback(ErrorCallback callback);
    void setCloseCallback(CloseCallback callback);


    bool subscribeOrderBook(const std::vector<std::string>& instIds);
    bool unsubscribeOrderBook(const std::vector<std::string>& instIds);

    bool subscribeBBO(const std::vector<std::string>& instIds);
    bool unsubscribeBBO(const std::vector<std::string>& instIds);

    bool subscribeMarkPrice(const std::vector<std::string>& instIds);
    bool unsubscribeMarkPrice(const std::vector<std::string>& instIds);

private:
    void init();
    context_ptr onTlsInit(websocketpp::connection_hdl hdl);
    void onOpen(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, message_ptr msg);
    void onClose(websocketpp::connection_hdl hdl);
    void onFail(websocketpp::connection_hdl hdl);

    std::string host_;
    bool connected_;
    client_type client_;
    websocketpp::connection_hdl connection_;
    std::thread asioThread_;

    MessageCallback messageCallback_;
    ConnectionCallback connectionCallback_;
    ErrorCallback errorCallback_;
    CloseCallback closeCallback_;
};

} // namespace public_api
} // namespace websocket
} // namespace rapdix 