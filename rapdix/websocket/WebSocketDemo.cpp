#include "WebSocketClient.h"
#include <openssl/hmac.h>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "request/UserLoginRequest.h"
#include "request/PlaceOrderRequest.h"
#include "request/CancelOrdersRequest.h"
#include <thread>
#include <chrono>
#include "../util/Config.h"
#include <mutex>
#include <condition_variable>
#include <memory>

using namespace rapdix::websocket;
using namespace rapdix::websocket::request;

class WebSocketTester {
public:
    static void testPlaceOrder() {
        WebSocketClient client(Config::WS_HOST, Config::API_KEY, Config::SECRET_KEY);
        
        client.setMessageCallback([](const std::string& msg) {
            std::cout << "收到消息: " << msg << std::endl;
        });
        
        client.setErrorCallback([](const std::string& error) {
            std::cerr << "发生错误: " << error << std::endl;
        });
        
        client.setConnectionCallback([]() {
            std::cout << "已连接" << std::endl;
        });
        
        if (!client.connect()) {
            std::cerr << "连接失败" << std::endl;
            return;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        auto args = PlaceOrderArgs::create()
            .sym("BINANCE_PERP_BTC_USDT")
            .side("BUY")
            .orderType("LIMIT")
            .orderQty("0.01")
            .limitPrice("30000")
            .timeInForce("GTC")
            .build();

        auto request = PlaceOrderRequest::create()
            .id(std::to_string(std::chrono::system_clock::now().time_since_epoch().count()))
            .args(args)
            .build();

        std::cout << "发送请求: " << request.toJsonString() << std::endl;

        if (client.placeOrder(request)) {
            std::cout << "下单请求已发送" << std::endl;
        } else {
            std::cerr << "下单请求发送失败" << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        client.disconnect();
    }
    
    static void testCancelOrder() {
        auto client = std::make_shared<WebSocketClient>(Config::WS_HOST, Config::API_KEY, Config::SECRET_KEY);
        
        bool receivedResponse = false;
        std::mutex mtx;
        std::condition_variable cv;
        
        client->setMessageCallback([&](const std::string& msg) {
            std::cout << "收到消息: " << msg << std::endl;
            {
                std::lock_guard<std::mutex> lock(mtx);
                receivedResponse = true;
            }
            cv.notify_one();
        });
        
        client->setErrorCallback([](const std::string& error) {
            std::cerr << "错误: " << error << std::endl;
        });
        
        client->setConnectionCallback([]() {
            std::cout << "已连接" << std::endl;
        });
        
        client->setCloseCallback([]() {
            std::cout << "连接已关闭" << std::endl;
        });
        
        if (!client->connect()) {
            std::cerr << "连接失败" << std::endl;
            return;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        try {
            auto args = CancelOrderArgs::create()
                .orderId("2010569771092035")
                .build();
            
            auto request = CancelOrderRequest::create()
                .id(std::to_string(std::chrono::system_clock::now().time_since_epoch().count()))
                .args(args)
                .build();
            
            std::cout << "发送请求: " << request.toJsonString() << std::endl;
            
            if (client->cancelOrder(request)) {
                std::cout << "取消订单请求已发送" << std::endl;
                
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    if (!cv.wait_for(lock, std::chrono::seconds(10), [&]{ return receivedResponse; })) {
                        std::cout << "等待响应超时" << std::endl;
                    }
                }
            } else {
                std::cerr << "取消订单请求发送失败" << std::endl;
            }
            
        } catch (const std::exception& e) {
            std::cerr << "发生异常: " << e.what() << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        client->disconnect();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        client.reset();
    }
    
    static void testCancelOrders() {
        auto client = std::make_shared<WebSocketClient>(Config::WS_HOST, Config::API_KEY, Config::SECRET_KEY);
        
        bool receivedResponse = false;
        std::mutex mtx;
        std::condition_variable cv;
        
        client->setMessageCallback([&](const std::string& msg) {
            std::cout << "收到消息: " << msg << std::endl;
            {
                std::lock_guard<std::mutex> lock(mtx);
                receivedResponse = true;
            }
            cv.notify_one();
        });
        
        client->setErrorCallback([](const std::string& error) {
            std::cerr << "错误: " << error << std::endl;
        });
        
        client->setConnectionCallback([]() {
            std::cout << "已连接" << std::endl;
        });
        
        client->setCloseCallback([]() {
            std::cout << "连接已关闭" << std::endl;
        });
        
        if (!client->connect()) {
            std::cerr << "连接失败" << std::endl;
            return;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        try {
            auto args = CancelOrdersArgs::builder()
                .exchangeType("BINANCE_PERP")
                .build();
            
            auto request = CancelOrdersRequest::builder()
                .id(std::to_string(std::chrono::system_clock::now().time_since_epoch().count()))
                .args(args)
                .build();
            
            std::cout << "发送请求: " << request.toJsonString() << std::endl;
            
            if (client->cancelOrders(request)) {
                std::cout << "批量取消订单请求已发送" << std::endl;
                
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    if (!cv.wait_for(lock, std::chrono::seconds(10), [&]{ return receivedResponse; })) {
                        std::cout << "等待响应超时" << std::endl;
                    }
                }
            } else {
                std::cerr << "批量取消订单请求发送失败" << std::endl;
            }
            
        } catch (const std::exception& e) {
            std::cerr << "发生异常: " << e.what() << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        client->disconnect();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        client.reset();
    }
    
    // static void testQueryOrder() { ... }
};

int main() {
    //WebSocketTester::testPlaceOrder();
    //WebSocketTester::testCancelOrder();
    WebSocketTester::testCancelOrders();
    return 0;
} 