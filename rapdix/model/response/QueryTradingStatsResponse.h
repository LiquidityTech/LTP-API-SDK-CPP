#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryTradingStatsResponse {
public:
    struct TradingDetail {
        std::string exchange;
        std::string businessType;
        std::string executedAmount;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TradingDetail,
            exchange, businessType, executedAmount)
    };

    QueryTradingStatsResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::string& getBegin() const { return begin; }
    const std::string& getEnd() const { return end; }
    const std::string& getAllSpot() const { return allSpot; }
    const std::string& getAllPerp() const { return allPerp; }
    const std::vector<TradingDetail>& getDetails() const { return details; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryTradingStatsResponse& response) {
        os << "QueryTradingStatsResponse{code=" << response.code 
           << ", message='" << response.message << "'"
           << ", begin='" << response.begin << "'"
           << ", end='" << response.end << "'"
           << ", allSpot='" << response.allSpot << "'"
           << ", allPerp='" << response.allPerp << "'";
        if (!response.details.empty()) {
            os << ", details=[";
            for (const auto& detail : response.details) {
                os << "\n  {exchange='" << detail.exchange
                   << "', businessType='" << detail.businessType
                   << "', executedAmount='" << detail.executedAmount
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryTradingStatsResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        
        // 只有在请求成功且data不为空时才解析data字段
        if (j.contains("data") && !j.at("data").is_null() && response.code == 200000) {
            const auto& data = j.at("data");
            data.at("begin").get_to(response.begin);
            data.at("end").get_to(response.end);
            data.at("allSpot").get_to(response.allSpot);
            data.at("allPerp").get_to(response.allPerp);
            if (data.contains("details") && !data.at("details").is_null()) {
                data.at("details").get_to(response.details);
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryTradingStatsResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message},
            {"data", {
                {"begin", response.begin},
                {"end", response.end},
                {"allSpot", response.allSpot},
                {"allPerp", response.allPerp},
                {"details", response.details}
            }}
        };
    }
    
private:
    int code;
    std::string message;
    std::string begin;
    std::string end;
    std::string allSpot;
    std::string allPerp;
    std::vector<TradingDetail> details;
}; 