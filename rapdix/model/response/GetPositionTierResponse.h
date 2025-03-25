#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetPositionTierResponse {
public:
    struct TierData {
        std::string sym;
        std::string minNotionalValue;
        std::string maxNotionalValue;
        std::string maxLeverage;
        std::string mmRate;
        std::string riskLevel;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TierData,
            sym, minNotionalValue, maxNotionalValue, maxLeverage, mmRate, riskLevel)
    };

    GetPositionTierResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<TierData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetPositionTierResponse& response) {
        os << "GetPositionTierResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", tiers=[";
            for (const auto& tier : response.data) {
                os << "\n  {sym='" << tier.sym
                   << "', minNotionalValue='" << tier.minNotionalValue
                   << "', maxNotionalValue='" << tier.maxNotionalValue
                   << "', maxLeverage='" << tier.maxLeverage
                   << "', mmRate='" << tier.mmRate
                   << "', riskLevel='" << tier.riskLevel
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetPositionTierResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& data = j.at("data");
            if (data.is_array()) {
                response.data = data.get<std::vector<TierData>>();
            }
            // 如果是空对象 {}，就保持 data 为空数组
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetPositionTierResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", response.data}
        };
    }
    
private:
    int code;
    std::string message;
    std::vector<TierData> data;
}; 