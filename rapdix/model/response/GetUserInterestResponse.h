#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetUserInterestResponse {
public:
    struct InterestData {
        int level;
        std::string exchangeType;
        std::string coin;
        std::string hourInterestRate;
        std::string loanLimit;
        int64_t updateTime;  // 使用 int64_t 因为时间戳是数字
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(InterestData,
            level, exchangeType, coin, hourInterestRate, loanLimit, updateTime)
    };

    GetUserInterestResponse() {}
    
    // Getters
    const std::vector<InterestData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetUserInterestResponse& response) {
        os << "GetUserInterestResponse{interests=[";
        if (!response.data.empty()) {
            for (const auto& interest : response.data) {
                os << "\n  {level=" << interest.level
                   << ", exchangeType='" << interest.exchangeType
                   << "', coin='" << interest.coin
                   << "', hourInterestRate='" << interest.hourInterestRate
                   << "', loanLimit='" << interest.loanLimit
                   << "', updateTime=" << interest.updateTime
                   << "}";
            }
            os << "\n";
        }
        os << "]}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetUserInterestResponse& response) {
        // 遍历所有 exchangeType 的数组
        for (const auto& item : j.items()) {
            const auto& interestArray = item.value();
            if (interestArray.is_array()) {
                // 将每个数组元素转换为 InterestData 并添加到 data 中
                for (const auto& interestData : interestArray) {
                    response.data.push_back(interestData.get<InterestData>());
                }
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetUserInterestResponse& response) {
        // 按 exchangeType 分组
        std::map<std::string, std::vector<InterestData>> grouped;
        for (const auto& interest : response.data) {
            grouped[interest.exchangeType].push_back(interest);
        }
        
        // 构造 JSON
        for (const auto& group : grouped) {
            j[group.first] = group.second;
        }
    }
    
private:
    std::vector<InterestData> data;
}; 