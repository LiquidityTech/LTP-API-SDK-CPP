#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class ReplaceOrderResponse {
public:
    ReplaceOrderResponse() = default;
    
    ReplaceOrderResponse(int code, const std::string& message, 
                        const std::string& orderId, const std::string& orderState)
        : code(code), message(message) {
        data.orderId = orderId;
        data.orderState = orderState;
    }
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::string& getOrderId() const { return data.orderId; }
    const std::string& getOrderState() const { return data.orderState; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ReplaceOrderResponse& response) {
        os << "ReplaceOrderResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (response.data.orderId.empty()) {
            os << "}";
        } else {
            os << ", orderId='" << response.data.orderId 
               << "', orderState='" << response.data.orderState << "'}";
        }
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ReplaceOrderResponse, code, message, data)
    
private:
    int code;
    std::string message;
    struct Data {
        std::string orderId;
        std::string orderState;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Data, orderId, orderState)
    } data;
}; 