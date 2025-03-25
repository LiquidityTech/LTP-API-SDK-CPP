#include "PublicWebSocketClient.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <thread>
#include <zlib.h>
#include <sstream>
#include <vector>

namespace rapdix {
namespace websocket {
namespace public_api {

PublicWebSocketClient::PublicWebSocketClient(const std::string& host)
    : host_(host), connected_(false) {
    init();
}

PublicWebSocketClient::~PublicWebSocketClient() {
    disconnect();
    if (asioThread_.joinable()) {
        asioThread_.join();
    }
}

void PublicWebSocketClient::init() {
    client_.clear_access_channels(websocketpp::log::alevel::all);
    client_.clear_error_channels(websocketpp::log::elevel::all);

    client_.init_asio();
    client_.set_tls_init_handler(bind(&PublicWebSocketClient::onTlsInit, this, _1));
    client_.set_open_handler(bind(&PublicWebSocketClient::onOpen, this, _1));
    client_.set_message_handler(bind(&PublicWebSocketClient::onMessage, this, _1, _2));
    client_.set_close_handler(bind(&PublicWebSocketClient::onClose, this, _1));
    client_.set_fail_handler(bind(&PublicWebSocketClient::onFail, this, _1));
}

bool PublicWebSocketClient::connect() {
    websocketpp::lib::error_code ec;
    client_type::connection_ptr con = client_.get_connection(host_, ec);
    if (ec) {
        if (errorCallback_) {
            errorCallback_("Failed to get connection: " + ec.message());
        }
        return false;
    }

    connection_ = con->get_handle();
    client_.connect(con);

    asioThread_ = std::thread([this]() {
        try {
            client_.run();
        } catch (const std::exception& e) {
            if (errorCallback_) {
                errorCallback_("ASIO Thread Exception: " + std::string(e.what()));
            }
        }
    });

    return true;
}

void PublicWebSocketClient::disconnect() {
    if (isConnected()) {
        websocketpp::lib::error_code ec;
        client_.close(connection_, websocketpp::close::status::normal, "", ec);
        connected_ = false;
        
        if (asioThread_.joinable()) {
            asioThread_.join();
        }
    }
}

bool PublicWebSocketClient::isConnected() const {
    return connected_;
}

bool PublicWebSocketClient::send(const std::string& message) {
    if (!isConnected()) {
        if (errorCallback_) {
            errorCallback_("unconnected");
        }
        return false;
    }

    websocketpp::lib::error_code ec;
    client_.send(connection_, message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        if (errorCallback_) {
            errorCallback_("send error: " + ec.message());
        }
        return false;
    }
    return true;
}

bool PublicWebSocketClient::subscribeOrderBook(const std::vector<std::string>& instIds) {
    nlohmann::json args;
    for (const auto& instId : instIds) {
        args["arg"].push_back({
            {"channel", "ORDER_BOOK"},
            {"instId", instId}
        });
    }
    args["event"] = "SUBSCRIBE";
    
    return send(args.dump());
}

bool PublicWebSocketClient::unsubscribeOrderBook(const std::vector<std::string>& instIds) {
    nlohmann::json args;
    for (const auto& instId : instIds) {
        args["arg"].push_back({
            {"channel", "ORDER_BOOK"},
            {"instId", instId}
        });
    }
    args["event"] = "UNSUBSCRIBE";
    
    return send(args.dump());
}

bool PublicWebSocketClient::subscribeBBO(const std::vector<std::string>& instIds) {
    nlohmann::json args;
    for (const auto& instId : instIds) {
        args["arg"].push_back({
            {"channel", "BBO"},
            {"instId", instId}
        });
    }
    args["event"] = "SUBSCRIBE";
    
    return send(args.dump());
}

bool PublicWebSocketClient::unsubscribeBBO(const std::vector<std::string>& instIds) {
    nlohmann::json args;
    for (const auto& instId : instIds) {
        args["arg"].push_back({
            {"channel", "BBO"},
            {"instId", instId}
        });
    }
    args["event"] = "UNSUBSCRIBE";
    
    return send(args.dump());
}

bool PublicWebSocketClient::subscribeMarkPrice(const std::vector<std::string>& instIds) {
    nlohmann::json args;
    for (const auto& instId : instIds) {
        args["arg"].push_back({
            {"channel", "MARK_PRICE"},
            {"instId", instId}
        });
    }
    args["event"] = "SUBSCRIBE";
    
    return send(args.dump());
}

bool PublicWebSocketClient::unsubscribeMarkPrice(const std::vector<std::string>& instIds) {
    nlohmann::json args;
    for (const auto& instId : instIds) {
        args["arg"].push_back({
            {"channel", "MARK_PRICE"},
            {"instId", instId}
        });
    }
    args["event"] = "UNSUBSCRIBE";
    
    return send(args.dump());
}

context_ptr PublicWebSocketClient::onTlsInit(websocketpp::connection_hdl hdl) {
    namespace asio = websocketpp::lib::asio;
    
    context_ptr ctx = websocketpp::lib::make_shared<asio::ssl::context>(asio::ssl::context::sslv23);
    try {
        ctx->set_options(
            asio::ssl::context::default_workarounds |
            asio::ssl::context::no_sslv2 |
            asio::ssl::context::no_sslv3 |
            asio::ssl::context::single_dh_use
        );
    } catch (const std::exception& e) {
        if (errorCallback_) {
            errorCallback_("TLS error: " + std::string(e.what()));
        }
    }
    return ctx;
}

void PublicWebSocketClient::onOpen(websocketpp::connection_hdl hdl) {
    std::cout << "connected" << std::endl;
    connected_ = true;
    if (connectionCallback_) {
        connectionCallback_("connected");
    }
}

void PublicWebSocketClient::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    try {
        if (msg->get_opcode() == websocketpp::frame::opcode::binary) {
            const std::string& compressed = msg->get_payload();
            
            z_stream zs;
            memset(&zs, 0, sizeof(zs));
            
            if (inflateInit2(&zs, 15 | 16) != Z_OK) {
                if (errorCallback_) {
                    errorCallback_("Failed to initialize zlib decompressor");
                }
                return;
            }
            
            zs.next_in = (Bytef*)compressed.data();
            zs.avail_in = static_cast<uInt>(compressed.size());
            
            const int CHUNK_SIZE = 32768;
            std::vector<char> buffer(CHUNK_SIZE);
            std::string decompressed;
            
            int ret;
            do {
                zs.next_out = reinterpret_cast<Bytef*>(buffer.data());
                zs.avail_out = buffer.size();
                
                ret = inflate(&zs, Z_NO_FLUSH);
                switch (ret) {
                    case Z_NEED_DICT:
                    case Z_DATA_ERROR:
                    case Z_MEM_ERROR:
                        inflateEnd(&zs);
                        if (errorCallback_) {
                            errorCallback_("decompress error: " + std::to_string(ret));
                        }
                        return;
                }
                
                decompressed.append(buffer.data(), buffer.size() - zs.avail_out);
            } while (zs.avail_out == 0);
            
            inflateEnd(&zs);
            
            std::cout << decompressed.substr(0, 200) << std::endl;
            
            try {
                auto json = nlohmann::json::parse(decompressed);
                if (messageCallback_) {
                    messageCallback_(json.dump(2)); 
                }
            } catch (const nlohmann::json::exception& e) {
                if (errorCallback_) {
                    errorCallback_("JSON parsing error: " + std::string(e.what()) + "\ndata: " + decompressed.substr(0, 100));
                }
            }
        } else {
            std::cout << "text message: " << msg->get_payload() << std::endl;
            if (messageCallback_) {
                messageCallback_(msg->get_payload());
            }
        }
    } catch (const std::exception& e) {
        if (errorCallback_) {
            errorCallback_(std::string("message error: ") + e.what());
        }
    }
}

void PublicWebSocketClient::onClose(websocketpp::connection_hdl hdl) {
    std::cout << "connection closed" << std::endl;
    connected_ = false;
    if (closeCallback_) {
        closeCallback_("connection closed");
    }
}

void PublicWebSocketClient::onFail(websocketpp::connection_hdl hdl) {
    std::cout << "connection failed" << std::endl;
    connected_ = false;
    if (errorCallback_) {
        errorCallback_("connection failed");
    }
}

void PublicWebSocketClient::setMessageCallback(MessageCallback callback) {
    messageCallback_ = callback;
}

void PublicWebSocketClient::setConnectionCallback(ConnectionCallback callback) {
    connectionCallback_ = callback;
}

void PublicWebSocketClient::setErrorCallback(ErrorCallback callback) {
    errorCallback_ = callback;
}

void PublicWebSocketClient::setCloseCallback(CloseCallback callback) {
    closeCallback_ = callback;
}

void testOrderBook() {
    auto client = std::make_shared<PublicWebSocketClient>("wss://mds.liquiditytech.com/v2/public");
    
    client->setMessageCallback([](const std::string& msg) {
        std::cout << "Message received: " << msg << std::endl;
    });

    client->setConnectionCallback([](const std::string& msg) {
        std::cout << "Connected: " << msg << std::endl;
    });

    client->setErrorCallback([](const std::string& msg) {
        std::cerr << "Error: " << msg << std::endl;
    });

    client->setCloseCallback([](const std::string& msg) {
        std::cout << "Connection closed: " << msg << std::endl;
    });

    if (!client->connect()) {
        std::cerr << "collection error" << std::endl;
        return;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<std::string> instIds = {
        "BINANCE_PERP_BTC_USDT"
    };
    
    if (client->subscribeOrderBook(instIds)) {
        std::cout << "Subscription request sent" << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(30));
        
        if (client->unsubscribeOrderBook(instIds)) {
            std::cout << "Unsubscription request sent" << std::endl;
        }
    }

    client->disconnect();
}

} // namespace public_api
} // namespace websocket
} // namespace rapdix 