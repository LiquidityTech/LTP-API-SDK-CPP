#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetFeeRateResponse {
public:
    struct FeeRateData {
        std::string portfolioId;
        std::string exchange;
        std::string instType;
        std::string effDate;
        std::string maker;
        std::string taker;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FeeRateData,
            portfolioId, exchange, instType, effDate, maker, taker)
    };

    GetFeeRateResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<FeeRateData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetFeeRateResponse& response) {
        os << "GetFeeRateResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", feeRates=[";
            for (const auto& feeRate : response.data) {
                os << "\n  {portfolioId='" << feeRate.portfolioId
                   << "', exchange='" << feeRate.exchange
                   << "', instType='" << feeRate.instType
                   << "', effDate='" << feeRate.effDate
                   << "', maker='" << feeRate.maker
                   << "', taker='" << feeRate.taker
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetFeeRateResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        
        if (j.contains("data") && !j.at("data").is_null()) {
            const auto& dataArray = j.at("data");
            if (dataArray.is_array()) {
                response.data = dataArray.get<std::vector<FeeRateData>>();
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetFeeRateResponse& response) {
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