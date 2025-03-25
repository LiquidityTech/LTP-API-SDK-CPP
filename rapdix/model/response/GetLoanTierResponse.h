#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetLoanTierResponse {
public:
    struct LoanTierData {
        std::string exchangeType;
        std::string coin;
        std::string tier;
        std::string minSize;
        std::string maxSize;
        std::string mmRate;
        std::string maxLeverage;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoanTierData,
            exchangeType, coin, tier, minSize, maxSize, mmRate, maxLeverage)
    };

    GetLoanTierResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<LoanTierData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetLoanTierResponse& response) {
        os << "GetLoanTierResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", loanTiers=[";
            for (const auto& tier : response.data) {
                os << "\n  {exchangeType='" << tier.exchangeType
                   << "', coin='" << tier.coin
                   << "', tier='" << tier.tier
                   << "', minSize='" << tier.minSize
                   << "', maxSize='" << tier.maxSize
                   << "', mmRate='" << tier.mmRate
                   << "', maxLeverage='" << tier.maxLeverage
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetLoanTierResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& data = j.at("data");
            if (data.is_array()) {
                response.data = data.get<std::vector<LoanTierData>>();
            }
            // 如果是空对象 {}，就保持 data 为空数组
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetLoanTierResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", response.data}
        };
    }
    
private:
    int code;
    std::string message;
    std::vector<LoanTierData> data;
}; 