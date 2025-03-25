#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetUserFeeRateResponse {
public:
    struct FeeRateData {
        std::string exchangeType;
        std::string businessType;
        std::string takerFeeRate;
        std::string makerFeeRate;
        std::string level;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FeeRateData,
            exchangeType, businessType, takerFeeRate, makerFeeRate, level)
    };

    GetUserFeeRateResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<FeeRateData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetUserFeeRateResponse& response) {
        os << "GetUserFeeRateResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", feeRates=[";
            for (const auto& rate : response.data) {
                os << "\n  {exchangeType='" << rate.exchangeType
                   << "', businessType='" << rate.businessType
                   << "', takerFeeRate='" << rate.takerFeeRate
                   << "', makerFeeRate='" << rate.makerFeeRate
                   << "', level='" << rate.level
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetUserFeeRateResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& data = j.at("data");
            if (data.is_array()) {
                response.data = data.get<std::vector<FeeRateData>>();
            }
            // 如果是空对象 {}，就保持 data 为空数组
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetUserFeeRateResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", response.data}
        };
    }
    
private:
    int code;
    std::string message;
    std::vector<FeeRateData> data;
}; 