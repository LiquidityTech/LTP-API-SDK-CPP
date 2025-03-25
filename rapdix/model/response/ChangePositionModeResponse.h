#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class ChangePositionModeResponse {
public:
    ChangePositionModeResponse() = default;
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ChangePositionModeResponse& response) {
        os << "ChangePositionModeResponse{code=" << response.code 
           << ", message='" << response.message << "'}";
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChangePositionModeResponse, code, message)
    
private:
    int code;
    std::string message;
}; 