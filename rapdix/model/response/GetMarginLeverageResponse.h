#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class GetMarginLeverageResponse {
public:
    struct LeverageData {
        std::string coin;
        std::string exchangeType;
        std::string leverage;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(LeverageData,
            coin, exchangeType, leverage)
    };

    struct PageData {
        int page;
        int pageSize;
        int totalSize;
        std::vector<LeverageData> list;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PageData,
            page, pageSize, totalSize, list)
    };

    GetMarginLeverageResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const PageData& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetMarginLeverageResponse& response) {
        os << "GetMarginLeverageResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.list.empty()) {
            os << ", page=" << response.data.page
               << ", pageSize=" << response.data.pageSize
               << ", totalSize=" << response.data.totalSize
               << ", leverages=[";
            for (const auto& leverage : response.data.list) {
                os << "\n  {coin='" << leverage.coin
                   << "', exchangeType='" << leverage.exchangeType
                   << "', leverage='" << leverage.leverage
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetMarginLeverageResponse, code, message, data)
    
private:
    int code;
    std::string message;
    PageData data;
}; 