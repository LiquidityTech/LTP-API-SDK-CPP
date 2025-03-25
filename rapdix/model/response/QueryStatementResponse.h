#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryStatementResponse {
public:
    struct StatementData {
        std::string portfolioId;
        std::string requestId;
        std::string statementId;
        std::string coin;
        std::string sym;
        std::string statementType;
        std::string exchangeType;
        std::string businessType;
        std::string beforeAvailable;
        std::string afterAvailable;
        std::string beforeOverdraw;
        std::string afterOverdraw;
        std::string createAt;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(StatementData,
            portfolioId, requestId, statementId, coin, sym,
            statementType, exchangeType, businessType,
            beforeAvailable, afterAvailable, beforeOverdraw,
            afterOverdraw, createAt)
    };

    struct PageData {
        int page;
        int pageSize;
        int totalSize;
        std::vector<StatementData> list;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PageData,
            page, pageSize, totalSize, list)
    };

    QueryStatementResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const PageData& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryStatementResponse& response) {
        os << "QueryStatementResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.list.empty()) {
            os << ", page=" << response.data.page
               << ", pageSize=" << response.data.pageSize
               << ", totalSize=" << response.data.totalSize
               << ", statements=[";
            for (const auto& statement : response.data.list) {
                os << "\n  {statementId='" << statement.statementId
                   << "', coin='" << statement.coin
                   << "', sym='" << statement.sym
                   << "', statementType='" << statement.statementType
                   << "', beforeAvailable='" << statement.beforeAvailable
                   << "', afterAvailable='" << statement.afterAvailable
                   << "', createAt='" << statement.createAt
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryStatementResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data") && !j.at("data").is_null()) {
            j.at("data").get_to(response.data);
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryStatementResponse& response) {
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