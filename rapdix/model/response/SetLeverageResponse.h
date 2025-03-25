#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class SetLeverageResponse {
public:
    SetLeverageResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const SetLeverageResponse& response) {
        os << "SetLeverageResponse{code=" << response.code 
           << ", message='" << response.message << "'}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, SetLeverageResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
    }
    
    friend void to_json(nlohmann::json& j, const SetLeverageResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
    }
    
private:
    int code;
    std::string message;
}; 