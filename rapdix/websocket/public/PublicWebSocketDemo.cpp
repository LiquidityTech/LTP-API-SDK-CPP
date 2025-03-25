#include "PublicWebSocketClient.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <nlohmann/json.hpp>

using namespace rapdix::websocket::public_api;

class PublicWebSocketTester {
public:
    static void testBBO() {
        auto client = std::make_shared<PublicWebSocketClient>("wss://mds.liquiditytech.com/v2/public");
        
        // 设置消息回调
        client->setMessageCallback([](const std::string& msg) {
            try {
                auto json = nlohmann::json::parse(msg);
                if (json.contains("channel") && json["channel"] == "BBO") {
                    std::cout << "收到BBO数据:" << std::endl;
                    std::cout << "交易对: " << json["instId"].get<std::string>() << std::endl;
                    std::cout << "最优买价: " << json["bid"]["price"].get<std::string>() 
                             << ", 数量: " << json["bid"]["qty"].get<std::string>() << std::endl;
                    std::cout << "最优卖价: " << json["ask"]["price"].get<std::string>() 
                             << ", 数量: " << json["ask"]["qty"].get<std::string>() << std::endl;
                    std::cout << "交易所时间: " << json["exchangeTs"].get<int64_t>() << std::endl;
                    std::cout << "本地时间: " << json["localTs"].get<int64_t>() << std::endl;
                    std::cout << "序列号: " << json["seqNum"].get<int64_t>() << std::endl;
                    std::cout << "交易所: " << json["exchange"].get<std::string>() << std::endl;
                    std::cout << "------------------------" << std::endl;
                } else {
                    // 其他消息（如订阅响应）
                    std::cout << json.dump(2) << std::endl;
                }
            } catch (const nlohmann::json::exception& e) {
                std::cout << "JSON解析错误: " << e.what() << std::endl;
                std::cout << "原始消息: " << msg << std::endl;
            }
        });

        // 设置连接回调
        client->setConnectionCallback([client](const std::string& msg) {
            std::cout << "已连接: " << msg << std::endl;
            
            // 连接成功后订阅BBO
            std::vector<std::string> instIds = {
                "BINANCE_PERP_BTC_USDT"
            };
            
            if (client->subscribeBBO(instIds)) {
                std::cout << "已发送BBO订阅请求" << std::endl;
            } else {
                std::cout << "发送BBO订阅请求失败" << std::endl;
            }
        });

        // 设置错误回调
        client->setErrorCallback([](const std::string& msg) {
            std::cerr << "错误: " << msg << std::endl;
        });

        // 设置关闭回调
        client->setCloseCallback([](const std::string& msg) {
            std::cout << "连接关闭: " << msg << std::endl;
        });

        // 连接到服务器
        if (!client->connect()) {
            std::cerr << "连接失败" << std::endl;
            return;
        }

        // 保持程序运行一段时间以接收消息
        std::this_thread::sleep_for(std::chrono::seconds(30));

        // 取消订阅
        std::vector<std::string> instIds = {
            "BINANCE_PERP_BTC_USDT"
        };
        if (client->unsubscribeBBO(instIds)) {
            std::cout << "已发送BBO取消订阅请求" << std::endl;
        }

        // 等待取消订阅响应
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // 断开连接
        client->disconnect();
    }

    static void testOrderBook() {
        auto client = std::make_shared<PublicWebSocketClient>("wss://mds.liquiditytech.com/v2/public");
        
        // 设置消息回调
        client->setMessageCallback([](const std::string& msg) {
            std::cout << "收到消息:" << std::endl;
            try {
                auto json = nlohmann::json::parse(msg);
                std::cout << json.dump(2) << std::endl;  // 格式化输出
            } catch (const nlohmann::json::exception& e) {
                std::cout << "原始消息内容: " << msg << std::endl;
                std::cout << "JSON解析错误: " << e.what() << std::endl;
            }
        });

        // 设置连接回调
        client->setConnectionCallback([client](const std::string& msg) {
            std::cout << "已连接: " << msg << std::endl;
            
            // 连接成功后订阅订单簿
            std::vector<std::string> instIds = {
                "BINANCE_PERP_BTC_USDT"
            };
            
            if (client->subscribeOrderBook(instIds)) {
                std::cout << "已发送订阅请求" << std::endl;
            } else {
                std::cout << "发送订阅请求失败" << std::endl;
            }
        });

        // 设置错误回调
        client->setErrorCallback([](const std::string& msg) {
            std::cerr << "错误: " << msg << std::endl;
        });

        // 设置关闭回调
        client->setCloseCallback([](const std::string& msg) {
            std::cout << "连接关闭: " << msg << std::endl;
        });

        // 连接到服务器
        if (!client->connect()) {
            std::cerr << "连接失败" << std::endl;
            return;
        }

        // 保持程序运行一段时间以接收消息
        std::this_thread::sleep_for(std::chrono::seconds(30));

        // 取消订阅
        std::vector<std::string> instIds = {
            "BINANCE_PERP_BTC_USDT"
        };
        if (client->unsubscribeOrderBook(instIds)) {
            std::cout << "已发送取消订阅请求" << std::endl;
        }

        // 等待取消订阅响应
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // 断开连接
        client->disconnect();
    }

    static void testMarkPrice() {
        auto client = std::make_shared<PublicWebSocketClient>("wss://mds.liquiditytech.com/v2/public");
        
        // 设置消息回调
        client->setMessageCallback([](const std::string& msg) {
            try {
                auto json = nlohmann::json::parse(msg);
                if (json.contains("channel") && json["channel"] == "MARK_PRICE") {
                    std::cout << "收到标记价格数据:" << std::endl;
                    std::cout << "交易对: " << json["instId"].get<std::string>() << std::endl;
                    std::cout << "标记价格: " << json["markPrice"].get<std::string>() << std::endl;
                    std::cout << "本地时间: " << json["localTs"].get<int64_t>() << std::endl;
                    std::cout << "------------------------" << std::endl;
                } else {
                    // 其他消息（如订阅响应）
                    std::cout << json.dump(2) << std::endl;
                }
            } catch (const nlohmann::json::exception& e) {
                std::cout << "JSON解析错误: " << e.what() << std::endl;
                std::cout << "原始消息: " << msg << std::endl;
            }
        });

        // 设置连接回调
        client->setConnectionCallback([client](const std::string& msg) {
            std::cout << "已连接: " << msg << std::endl;
            
            // 连接成功后订阅标记价格
            std::vector<std::string> instIds = {
                "BINANCE_PERP_BTC_USDT"
            };
            
            if (client->subscribeMarkPrice(instIds)) {
                std::cout << "已发送标记价格订阅请求" << std::endl;
            } else {
                std::cout << "发送标记价格订阅请求失败" << std::endl;
            }
        });

        client->setErrorCallback([](const std::string& msg) {
            std::cerr << "错误: " << msg << std::endl;
        });

        client->setCloseCallback([](const std::string& msg) {
            std::cout << "连接关闭: " << msg << std::endl;
        });

        if (!client->connect()) {
            std::cerr << "连接失败" << std::endl;
            return;
        }

        std::this_thread::sleep_for(std::chrono::seconds(30));

        std::vector<std::string> instIds = {
            "BINANCE_PERP_BTC_USDT"
        };
        if (client->unsubscribeMarkPrice(instIds)) {
            std::cout << "已发送标记价格取消订阅请求" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));

        client->disconnect();
    }
};

int main() {
    // PublicWebSocketTester::testOrderBook();
    // PublicWebSocketTester::testBBO();
    PublicWebSocketTester::testMarkPrice();
    return 0;
} 