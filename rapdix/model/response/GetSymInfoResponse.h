#pragma once
#include <string>
#include <map>
#include <ostream>
#include <nlohmann/json.hpp>

class GetSymInfoResponse {
public:
    struct SymInfo {
        std::string sym;
        std::string state;
        std::string pricePrecision;
        std::string qtyPrecision;
        std::string minNotional;
        std::string maxLimitSize;
        std::string lotSize;
        std::string tickSize;
        std::string maxNumOrders;
        std::string contractSize;
        std::string maxMarketSize;
        std::string minSize;
        std::string originalSymbol;
        std::string defaultLeverage;
        std::string liquidationFee;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(SymInfo,
            sym, state, pricePrecision, qtyPrecision, minNotional,
            maxLimitSize, lotSize, tickSize, maxNumOrders, contractSize,
            maxMarketSize, minSize, originalSymbol, defaultLeverage,
            liquidationFee)
    };

    GetSymInfoResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::map<std::string, SymInfo>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GetSymInfoResponse& response) {
        os << "GetSymInfoResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", symInfos=[";
            for (const auto& [key, info] : response.data) {
                os << "\n  {sym='" << info.sym
                   << "', state='" << info.state
                   << "', pricePrecision='" << info.pricePrecision
                   << "', qtyPrecision='" << info.qtyPrecision
                   << "', minNotional='" << info.minNotional
                   << "', maxLimitSize='" << info.maxLimitSize
                   << "', lotSize='" << info.lotSize
                   << "', tickSize='" << info.tickSize
                   << "', maxNumOrders='" << info.maxNumOrders
                   << "', contractSize='" << info.contractSize
                   << "', maxMarketSize='" << info.maxMarketSize
                   << "', minSize='" << info.minSize
                   << "', originalSymbol='" << info.originalSymbol
                   << "', defaultLeverage='" << info.defaultLeverage
                   << "', liquidationFee='" << info.liquidationFee
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // 自定义 JSON 序列化
    friend void from_json(const nlohmann::json& j, GetSymInfoResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            response.data = j.at("data").get<std::map<std::string, SymInfo>>();
        }
    }
    
    friend void to_json(nlohmann::json& j, const GetSymInfoResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", response.data}
        };
    }
    
private:
    int code;
    std::string message;
    std::map<std::string, SymInfo> data;  // 改用 map 而不是 vector
}; 