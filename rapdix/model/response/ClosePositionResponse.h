#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class ClosePositionResponse {
public:
    ClosePositionResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::string& getOrderId() const { return orderId; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ClosePositionResponse& response) {
        os << "ClosePositionResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.orderId.empty()) {
            os << ", orderId='" << response.orderId << "'";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, ClosePositionResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null() && 
            j.at("data").contains("orderId")) {  // 检查 data 中是否有 orderId
            j.at("data").at("orderId").get_to(response.orderId);
        }
    }
    
    friend void to_json(nlohmann::json& j, const ClosePositionResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        if (!response.orderId.empty()) {
            j["data"] = {{"orderId", response.orderId}};
        }
    }
    
private:
    int code;
    std::string message;
    std::string orderId;
}; 