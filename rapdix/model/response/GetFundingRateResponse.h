#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetFundingRateResponse {
public:
    struct FundingRateData {
        std::string sym;
        std::string fundingRate;
        std::string fundingTime;
        std::string nextFundingTime;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FundingRateData,
            sym, fundingRate, fundingTime, nextFundingTime)
    };

    GetFundingRateResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<FundingRateData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetFundingRateResponse& response) {
        os << "GetFundingRateResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", fundingRates=[";
            for (const auto& rate : response.data) {
                os << "\n  {sym='" << rate.sym
                   << "', fundingRate='" << rate.fundingRate
                   << "', fundingTime='" << rate.fundingTime
                   << "', nextFundingTime='" << rate.nextFundingTime
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetFundingRateResponse, code, message, data)
    
private:
    int code;
    std::string message;
    std::vector<FundingRateData> data;
}; 