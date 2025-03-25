#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetBrokerPositionTierResponse {
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

    GetBrokerPositionTierResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<TierData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetBrokerPositionTierResponse& response) {
        os << "GetBrokerPositionTierResponse{code=" << response.code 
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
    friend void from_json(const nlohmann::json& j, GetBrokerPositionTierResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& dataObj = j.at("data");
            // 遍历所有交易对的数组
            for (const auto& item : dataObj.items()) {
                const auto& tierArray = item.value();
                if (tierArray.is_array()) {
                    // 将每个数组元素转换为 TierData 并添加到 data 中
                    for (const auto& tierData : tierArray) {
                        response.data.push_back(tierData.get<TierData>());
                    }
                }
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetBrokerPositionTierResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        
        // 按 sym 分组
        std::map<std::string, std::vector<TierData>> grouped;
        for (const auto& tier : response.data) {
            grouped[tier.sym].push_back(tier);
        }
        
        // 构造嵌套的 JSON 结构
        nlohmann::json dataObj;
        for (const auto& group : grouped) {
            dataObj[group.first] = group.second;
        }
        j["data"] = dataObj;
    }
    
private:
    int code;
    std::string message;
    std::vector<TierData> data;
}; 