#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class SetMarginLeverageResponse {
public:
    SetMarginLeverageResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const SetMarginLeverageResponse& response) {
        os << "SetMarginLeverageResponse{code=" << response.code 
           << ", message='" << response.message << "'}";
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SetMarginLeverageResponse, code, message)
    
private:
    int code;
    std::string message;
}; 