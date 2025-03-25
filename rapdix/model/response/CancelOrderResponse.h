#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class CancelOrderResponse {
public:
    CancelOrderResponse() = default;
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const CancelOrderResponse& response) {
        os << "CancelOrderResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (response.data.orderId.empty()) {
            os << "}";
        } else {
            os << ", orderId='" << response.data.orderId 
               << "', clientOrderId='" << response.data.clientOrderId
               << "', orderState='" << response.data.orderState << "'}";
        }
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CancelOrderResponse, code, message, data)
    
private:
    int code;
    std::string message;
    struct Data {
        std::string orderId;
        std::string clientOrderId;
        std::string orderState;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Data, orderId, clientOrderId, orderState)
    } data;
}; 