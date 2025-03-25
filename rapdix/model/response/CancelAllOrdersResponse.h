#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class CancelAllOrdersResponse {
public:
    CancelAllOrdersResponse() = default;
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const CancelAllOrdersResponse& response) {
        os << "CancelAllOrdersResponse{code=" << response.code 
           << ", message='" << response.message << "'}";
        return os;
    }
    
    // 自定义 JSON 解析
    friend void from_json(const nlohmann::json& j, CancelAllOrdersResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        // data 字段可以是任何类型，我们不需要解析它
    }
    
    friend void to_json(nlohmann::json& j, const CancelAllOrdersResponse& response) {
        j = nlohmann::json{
            {"code", response.code},
            {"message", response.message}
        };
    }
    
private:
    int code;
    std::string message;
    // 移除 data 字段，因为我们不需要它
}; 