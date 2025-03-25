#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetMarkPriceResponse {
public:
    struct MarkPriceData {
        std::string publicChannelTypeEnum;
        std::string sym;
        std::string markPrice;
        int64_t time;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(MarkPriceData,
            publicChannelTypeEnum, sym, markPrice, time)
    };

    GetMarkPriceResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<MarkPriceData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetMarkPriceResponse& response) {
        os << "GetMarkPriceResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", markPrices=[";
            for (const auto& price : response.data) {
                os << "\n  {publicChannelTypeEnum='" << price.publicChannelTypeEnum
                   << "', sym='" << price.sym
                   << "', markPrice='" << price.markPrice
                   << "', time=" << price.time
                   << "}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetMarkPriceResponse, code, message, data)
    
private:
    int code;
    std::string message;
    std::vector<MarkPriceData> data;
}; 