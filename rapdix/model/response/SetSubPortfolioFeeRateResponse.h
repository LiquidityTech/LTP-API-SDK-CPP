#pragma once
#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

class SetSubPortfolioFeeRateResponse {
public:
    SetSubPortfolioFeeRateResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::string& getEffDate() const { return effDate; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const SetSubPortfolioFeeRateResponse& response) {
        os << "SetSubPortfolioFeeRateResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.effDate.empty()) {
            os << ", effDate='" << response.effDate << "'";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, SetSubPortfolioFeeRateResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        
        // effDate 是可选的
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& data = j.at("data");
            if (data.contains("effDate") && !data.at("effDate").is_null()) {
                data.at("effDate").get_to(response.effDate);
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const SetSubPortfolioFeeRateResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        
        if (!response.effDate.empty()) {
            j["data"] = {{"effDate", response.effDate}};
        }
    }
    
private:
    int code;
    std::string message;
    std::string effDate;
}; 