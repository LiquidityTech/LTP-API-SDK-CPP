#include "WebSocketClient.h"
#include <openssl/hmac.h>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "request/UserLoginRequest.h"
#include "request/PlaceOrderRequest.h"
#include <nlohmann/json.hpp>

using namespace rapdix::websocket::request;

namespace rapdix {
namespace websocket {

WebSocketClient::WebSocketClient(const std::string& uri, 
                                 const std::string& apiKey, 
                                 const std::string& secretKey)
    : uri_(uri), apiKey_(apiKey), secretKey_(secretKey), 
      connected_(false), stopHeartbeat_(false) {
    init();
}

WebSocketClient::~WebSocketClient() {
    try {
        stopHeartbeat();
        
        if (isConnected()) {
            disconnect();
        }
        
        endpoint_.stop_perpetual();
        
        if (asioThread_.joinable()) {
            asioThread_.join();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error in destructor: " << e.what() << std::endl;
    }
}

void WebSocketClient::init() {
    endpoint_.clear_access_channels(websocketpp::log::alevel::all);
    endpoint_.clear_error_channels(websocketpp::log::elevel::all);
    
    endpoint_.init_asio();
    endpoint_.start_perpetual();
    
    endpoint_.set_open_handshake_timeout(30000); 
    endpoint_.set_close_handshake_timeout(30000);
    endpoint_.set_pong_timeout(30000);

    endpoint_.set_tls_init_handler(bind(&WebSocketClient::onTlsInit, this, _1));
    endpoint_.set_message_handler(bind(&WebSocketClient::onMessage, this, _1, _2));
    endpoint_.set_open_handler(bind(&WebSocketClient::onOpen, this, _1));
    endpoint_.set_close_handler(bind(&WebSocketClient::onClose, this, _1));
    endpoint_.set_fail_handler(bind(&WebSocketClient::onFail, this, _1));
    
    asioThread_ = std::thread([this]() {
        endpoint_.run();
    });
}

bool WebSocketClient::connect() {
    websocketpp::lib::error_code ec;
    
    client::connection_ptr con = endpoint_.get_connection(uri_, ec);
    
    if (ec) {
        std::string error_msg = "Connect initialization error: " + ec.message();
        std::cerr << error_msg << std::endl;
        if (errorCallback_) {
            errorCallback_(error_msg);
        }
        return false;
    }
    
    try {
        con->add_subprotocol("v1.api.liquiditytech.com");
        con->set_proxy(""); 
        
        con->set_open_handshake_timeout(10000);
        con->set_close_handshake_timeout(10000);
        con->set_pong_timeout(10000);
        
        connection_ = con->get_handle();
        endpoint_.connect(con);
        
        std::cout << "Connecting to: " << uri_ << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::string error_msg = "Connection setup error: " + std::string(e.what());
        std::cerr << error_msg << std::endl;
        if (errorCallback_) {
            errorCallback_(error_msg);
        }
        return false;
    }
}

void WebSocketClient::disconnect() {
    if (isConnected()) {
        stopHeartbeat();
        
        websocketpp::lib::error_code ec;
        endpoint_.close(connection_, websocketpp::close::status::normal, "Closing connection", ec);
        
        if (ec) {
            std::cerr << "Warning during disconnect: " << ec.message() << std::endl;
        }
        
        connected_ = false;
    }
}

bool WebSocketClient::send(const std::string& message) {
    if (!isConnected()) {
        if (errorCallback_) {
            errorCallback_("Cannot send message, not connected");
        }
        return false;
    }
    
    websocketpp::lib::error_code ec;
    endpoint_.send(connection_, message, websocketpp::frame::opcode::text, ec);
    
    if (ec) {
        if (errorCallback_) {
            errorCallback_("Error sending message: " + ec.message());
        }
        return false;
    }
    
    return true;
}

void WebSocketClient::setMessageCallback(MessageCallback callback) {
    messageCallback_ = callback;
}

void WebSocketClient::setConnectionCallback(ConnectionCallback callback) {
    connectionCallback_ = callback;
}

void WebSocketClient::setErrorCallback(ErrorCallback callback) {
    errorCallback_ = callback;
}

void WebSocketClient::setCloseCallback(CloseCallback callback) {
    closeCallback_ = callback;
}

bool WebSocketClient::isConnected() const {
    return connected_;
}

context_ptr WebSocketClient::onTlsInit(websocketpp::connection_hdl hdl) {
    auto ctx = std::make_shared<asio::ssl::context>(asio::ssl::context::tlsv12);
    
    try {
        ctx->set_options(
            asio::ssl::context::default_workarounds |
            asio::ssl::context::no_sslv2 |
            asio::ssl::context::no_sslv3 |
            asio::ssl::context::single_dh_use
        );
        
        ctx->set_verify_mode(asio::ssl::verify_none);
        
    } catch (const std::exception& e) {
        std::cerr << "Error in TLS init: " << e.what() << std::endl;
        if (errorCallback_) {
            errorCallback_("TLS initialization error: " + std::string(e.what()));
        }
    }
    
    return ctx;
}

void WebSocketClient::onOpen(websocketpp::connection_hdl hdl) {
    std::cout << "Connection opened" << std::endl;
    connected_ = true;
    
    if (connectionCallback_) {
        connectionCallback_();
    }
    
    // 发送登录请求
    sendLoginRequest();
    
    // 启动心跳线程
    startHeartbeatThread();
}

void WebSocketClient::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::string payload = msg->get_payload();
    
    if (payload == "pong") {
        return;
    }

    if (messageCallback_) {
        messageCallback_(payload);
    }
}

void WebSocketClient::onClose(websocketpp::connection_hdl hdl) {
    connected_ = false;
    
    if (closeCallback_) {
        closeCallback_();
    }
}

void WebSocketClient::onFail(websocketpp::connection_hdl hdl) {
    connected_ = false;
    
    client::connection_ptr con = endpoint_.get_con_from_hdl(hdl);
    std::string error = "Connection failed: " + con->get_ec().message();
    
    if (errorCallback_) {
        errorCallback_(error);
    }
}

void WebSocketClient::sendLoginRequest() {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()
    ).count());
    
    std::string message = timestamp + "GET" + "/users/self/verify";
    std::string sign = generateSignature(message);

    auto loginArgs = LoginArgs::create()
        .apiKey(apiKey_)
        .timestamp(timestamp)
        .sign(sign)
        .build();
        
    auto loginRequest = UserLoginRequest::create()
        .action("login")
        .args(loginArgs)
        .build();
    
    send(loginRequest.toJsonString());
}

std::string WebSocketClient::generateSignature(const std::string& message) {
    unsigned char hmac[EVP_MAX_MD_SIZE];
    unsigned int hmac_len;
    
    HMAC(EVP_sha256(),
         secretKey_.c_str(), secretKey_.length(),
         reinterpret_cast<const unsigned char*>(message.c_str()), message.length(),
         hmac, &hmac_len);
    
    std::stringstream ss;
    for(unsigned int i = 0; i < hmac_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hmac[i];
    }
    
    return ss.str();
}

void WebSocketClient::startHeartbeatThread() {
    stopHeartbeat_ = false;  
    
    heartbeatThread_ = std::thread([this]() {
        while (!stopHeartbeat_) {  
            {
                std::unique_lock<std::mutex> lock(mutex_);
                if (cv_.wait_for(lock, std::chrono::seconds(20), 
                    [this]() { return stopHeartbeat_; })) {
                    break; 
                }
            }
            
            if (isConnected() && !stopHeartbeat_) {  
                send("ping");
            }
        }
    });
}

bool WebSocketClient::placeOrder(const request::PlaceOrderRequest& request) {
    if (!isConnected()) {
        if (errorCallback_) {
            errorCallback_("Cannot place order, not connected");
        }
        return false;
    }
    return send(request.toJsonString());
}

bool WebSocketClient::cancelOrder(const request::CancelOrderRequest& request) {
    if (!isConnected()) {
        if (errorCallback_) {
            errorCallback_("Cannot cancel order, not connected");
        }
        return false;
    }
    return send(request.toJsonString());
}

bool WebSocketClient::cancelOrders(const request::CancelOrdersRequest& request) {
    if (!isConnected()) {
        if (errorCallback_) {
            errorCallback_("Cannot cancel orders, not connected");
        }
        return false;
    }
    return send(request.toJsonString());
}

void WebSocketClient::stopHeartbeat() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stopHeartbeat_ = true;
    }
    cv_.notify_all();  
    
    if (heartbeatThread_.joinable()) {
        heartbeatThread_.join();
    }
}

} // namespace websocket
} // namespace rapdix 