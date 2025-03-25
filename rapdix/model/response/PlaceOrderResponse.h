#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class PlaceOrderResponse {
public:
    // Constructor
    PlaceOrderResponse() = default;
    
    // 构造函数
    PlaceOrderResponse(int code, const std::string& message, 
                      const std::string& orderId, const std::string& clientOrderId)
        : code(code), message(message) {
        data.orderId = orderId;
        data.clientOrderId = clientOrderId;
    }
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::string& getOrderId() const { return data.orderId; }
    const std::string& getClientOrderId() const { return data.clientOrderId; }
    
    // Setters
    void setOrderId(const std::string& newOrderId) { data.orderId = newOrderId; }
    void setClientOrderId(const std::string& newClientOrderId) { data.clientOrderId = newClientOrderId; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const PlaceOrderResponse& response) {
        os << "PlaceOrderResponse{code=" << response.code 
           << ", message='" << response.message 
           << "', orderId='" << response.data.orderId 
           << "', clientOrderId='" << response.data.clientOrderId << "'}";
        return os;
    }
    
    // 为 nlohmann/json 添加序列化支持
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlaceOrderResponse, code, message, data)
    
private:
    int code;
    std::string message;
    struct Data {
        std::string orderId;
        std::string clientOrderId;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Data, orderId, clientOrderId)
    } data;
}; 