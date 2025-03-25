#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryTransactionsPageableResponse {
public:
    struct TransactionData {
        std::string transactionId;
        std::string portfolioId;
        std::string orderId;
        std::string clientOrderId;
        std::string exchangeType;
        std::string businessType;
        std::string sym;
        std::string side;
        std::string quantity;
        std::string price;
        std::string tradingFee;
        std::string tradingFeeCoin;
        std::string execType;
        std::string rpnl;
        std::string createAt;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransactionData,
            transactionId, portfolioId, orderId, clientOrderId,
            exchangeType, businessType, sym, side, quantity,
            price, tradingFee, tradingFeeCoin, execType,
            rpnl, createAt)
    };

    struct PageData {
        int page;
        int pageSize;
        int totalSize;
        std::vector<TransactionData> list;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PageData,
            page, pageSize, totalSize, list)
    };

    QueryTransactionsPageableResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const PageData& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryTransactionsPageableResponse& response) {
        os << "QueryTransactionsPageableResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.list.empty()) {
            os << ", page=" << response.data.page
               << ", pageSize=" << response.data.pageSize
               << ", totalSize=" << response.data.totalSize
               << ", transactions=[";
            for (const auto& transaction : response.data.list) {
                os << "\n  {transactionId='" << transaction.transactionId
                   << "', orderId='" << transaction.orderId
                   << "', sym='" << transaction.sym
                   << "', side='" << transaction.side
                   << "', quantity='" << transaction.quantity
                   << "', price='" << transaction.price
                   << "', execType='" << transaction.execType
                   << "', rpnl='" << transaction.rpnl
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryTransactionsPageableResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            j.at("data").get_to(response.data);
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryTransactionsPageableResponse& response) {
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