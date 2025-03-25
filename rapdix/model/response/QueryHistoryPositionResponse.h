#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryHistoryPositionResponse {
public:
    struct HistoryPositionData {
        std::string positionId;
        std::string portfolioId;
        std::string portfolioName;
        std::string sym;
        std::string closedType;
        std::string closedPnl;
        std::string closedPnlRatio;
        std::string closedAvgPrice;
        std::string maxPositionQty;
        std::string closedQty;
        std::string liqFee;
        std::string fundingFee;
        std::string fee;
        std::string leverage;
        std::string openAvgPrice;
        std::string positionHistorySide;
        std::string createAt;
        std::string updateAt;
        std::string positionMode;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(HistoryPositionData,
            positionId, portfolioId, portfolioName, sym, closedType,
            closedPnl, closedPnlRatio, closedAvgPrice, maxPositionQty,
            closedQty, liqFee, fundingFee, fee, leverage, openAvgPrice,
            positionHistorySide, createAt, updateAt, positionMode)
    };

    struct PageData {
        int page;
        int pageSize;
        int totalSize;
        std::vector<HistoryPositionData> list;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PageData,
            page, pageSize, totalSize, list)
    };

    QueryHistoryPositionResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const PageData& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryHistoryPositionResponse& response) {
        os << "QueryHistoryPositionResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.list.empty()) {
            os << ", page=" << response.data.page
               << ", pageSize=" << response.data.pageSize
               << ", totalSize=" << response.data.totalSize
               << ", positions=[";
            for (const auto& position : response.data.list) {
                os << "\n  {positionId='" << position.positionId
                   << "', sym='" << position.sym
                   << "', closedType='" << position.closedType
                   << "', closedPnl='" << position.closedPnl
                   << "', closedPnlRatio='" << position.closedPnlRatio
                   << "', maxPositionQty='" << position.maxPositionQty
                   << "', closedQty='" << position.closedQty
                   << "', leverage='" << position.leverage
                   << "', positionHistorySide='" << position.positionHistorySide
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryHistoryPositionResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            j.at("data").get_to(response.data);
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryHistoryPositionResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        if (!response.data.list.empty()) {
            j["data"] = response.data;
        }
    }
    
private:
    int code;
    std::string message;
    PageData data;
}; 