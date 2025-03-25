#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryPortfolioFundsHistoryResponse {
public:
    struct FundsHistoryData {
        std::string id;
        std::string currency;
        std::string clientOrderId;
        std::string amount;
        std::string amountReceived;
        std::string networkFee;
        std::string network;
        std::string txId;
        std::string fromTradeAccountId;
        std::string toTradeAccountId;
        std::string fromAccountType;
        std::string toAccountType;
        std::string status;
        std::string type;
        std::string createdAt;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(FundsHistoryData,
            id, currency, clientOrderId, amount, amountReceived,
            networkFee, network, txId, fromTradeAccountId, toTradeAccountId,
            fromAccountType, toAccountType, status, type, createdAt)
    };

    QueryPortfolioFundsHistoryResponse() : code(0), data(std::vector<FundsHistoryData>()) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<FundsHistoryData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryPortfolioFundsHistoryResponse& response) {
        os << "QueryPortfolioFundsHistoryResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", history=[";
            for (const auto& history : response.data) {
                os << "\n  {id='" << history.id
                   << "', currency='" << history.currency
                   << "', amount='" << history.amount
                   << "', amountReceived='" << history.amountReceived
                   << "', networkFee='" << history.networkFee
                   << "', network='" << history.network
                   << "', txId='" << history.txId
                   << "', fromTradeAccountId='" << history.fromTradeAccountId
                   << "', toTradeAccountId='" << history.toTradeAccountId
                   << "', fromAccountType='" << history.fromAccountType
                   << "', toAccountType='" << history.toAccountType
                   << "', status='" << history.status
                   << "', type='" << history.type
                   << "', createdAt='" << history.createdAt
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryPortfolioFundsHistoryResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data")) {
            j.at("data").get_to(response.data);
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryPortfolioFundsHistoryResponse& response) {
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
    std::vector<FundsHistoryData> data;
}; 