#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryPositionResponse {
public:
    struct PositionData {
        std::string positionId;
        std::string portfolioId;
        std::string sym;
        std::string positionSide;
        std::string positionMargin;
        std::string positionMM;
        std::string positionQty;
        std::string positionValue;
        std::string unrealizedPNL;
        std::string unrealizedPNLRate;
        std::string avgPrice;
        std::string markPrice;
        std::string leverage;
        std::string maxLeverage;
        std::string riskLevel;
        std::string fee;
        std::string fundingFee;
        std::string createAt;
        std::string updateAt;
        std::string liqPrice;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PositionData,
            positionId, portfolioId, sym, positionSide, positionMargin,
            positionMM, positionQty, positionValue, unrealizedPNL,
            unrealizedPNLRate, avgPrice, markPrice, leverage, maxLeverage,
            riskLevel, fee, fundingFee, createAt, updateAt, liqPrice)
    };

    QueryPositionResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<PositionData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryPositionResponse& response) {
        os << "QueryPositionResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", positions=[";
            for (const auto& position : response.data) {
                os << "\n  {positionId='" << position.positionId
                   << "', sym='" << position.sym
                   << "', positionSide='" << position.positionSide
                   << "', positionQty='" << position.positionQty
                   << "', avgPrice='" << position.avgPrice
                   << "', markPrice='" << position.markPrice
                   << "', unrealizedPNL='" << position.unrealizedPNL
                   << "', leverage='" << position.leverage
                   << "', liqPrice='" << position.liqPrice
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryPositionResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            j.at("data").get_to(response.data);
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryPositionResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        if (!response.data.empty()) {
            j["data"] = response.data;
        }
    }
    
private:
    int code;
    std::string message;
    std::vector<PositionData> data;
}; 